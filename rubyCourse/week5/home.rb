require 'digest/sha1'

class State
  SUCCESS = true
  ERROR = false
  attr :message

  def initialize(message, status, result = nil)
    @message = message
    @success = status
    unless result.nil?
      @result = result
      self.class.send(:attr_accessor, :result)
    end
  end

  def success?
    @success
  end

  def error?
    not @success
  end
end

class Commit
  attr :hash, :date, :date_str, :message, :bucket

  def initialize(message, bucket)
    @message = message
    @date = Time.now
    @date_str = @date.strftime("%a %b %d %H:%M %Y %z")
    @hash = Digest::SHA1.hexdigest(@date_str + @message)
    @bucket = bucket
  end

  def has_object?(object_name)
    @bucket.has_key? object_name
  end

  def objects
    @bucket.values
  end
end

class Branch
  attr :commits, :name, :head

  def initialize(name)
    @name = name
    @commits = {}
    @head = Commit.new("initialize", {})
  end

  def commit(message, bucket, remove_list = [])
    commit_bucket = head.bucket.merge(bucket)
    commit_bucket.reject! { |name, object| remove_list.include? name }
    new_commit = Commit.new(message, commit_bucket)
    @commits[new_commit.hash] = new_commit
    @head = new_commit
  end

  def checkout(commit_hash)
    @commits.reverse_each do |hash, commit|
      break if hash == commit_hash
      @commits.delete(hash)
    end
    @head = @commits[commit_hash]
  end
end

class BranchTree
  attr :current_branch

  def initialize
    @branches = {"master" => Branch.new("master")}
    @current_branch = @branches["master"]
  end

  def create(branch_name)
    if @branches.has_key? branch_name
      State.new("Branch #{branch_name} already exists.", State::ERROR)
    else
      @branches[branch_name] = Branch.new(branch_name)
      @branches[branch_name].commits.update current_branch.commits
      State.new("Created branch #{branch_name}.", State::SUCCESS)
    end
  end

  def checkout(branch_name)
    if @branches.has_key? branch_name
      @current_branch = @branches[branch_name]
      State.new("Switched to branch #{branch_name}.", State::SUCCESS)
    else
      State.new("Branch #{branch_name} does not exist.", State::ERROR)
    end
  end

  def remove(branch_name)
    if current_branch.name == branch_name
      State.new("Cannot remove current branch.", State::ERROR)
    elsif @branches.has_key? branch_name
      @branches.delete(branch_name)
      State.new("Removed branch #{branch_name}.", State::SUCCESS)
    else
      State.new("Branch #{branch_name} does not exist.", State::ERROR)
    end
  end

  def list
    message = ""
    @branches.sort.each do |name, branch|
      message += (name == current_branch.name) ? "* #{name}\n" : "  #{name}\n"
    end
    State.new(message.rstrip, State::SUCCESS)
  end
end


class ObjectStore
  def initialize
    @added = {}
    @remove_list = []
    @tree = BranchTree.new
  end

  def self.init
    new_object = self.new
    new_object.instance_eval(&Proc.new) if block_given?
    new_object
  end

  private
  def current_branch
    @tree.current_branch
  end

  def current_head
    current_branch.head
  end

  public
  def add(name, object)
    @added[name] = object
    @remove_list.delete(name)
    State.new("Added #{name} to stage.", State::SUCCESS, object)
  end

  def commit(message)
    if @added.empty? && @remove_list.empty?
      State.new("Nothing to commit, working directory clean.", State::ERROR)
    else
      current_branch.commit(message, @added, @remove_list)
      count = @added.count + @remove_list.count
      @added, @remove_list = {}, []
      State.new("#{message}\n\t#{count} objects changed",
                State::SUCCESS,
                current_head)
    end
  end

  def remove(name)
    if current_head.has_object? name
      @remove_list << name
      State.new("Added #{name} for removal.",
                State::SUCCESS,
                current_head.bucket[name])
    else
      State.new("Object #{name} is not committed.", State::ERROR)
    end
  end

  def checkout(commit_hash)
    if current_branch.commits.has_key? commit_hash
      current_branch.checkout commit_hash
      State.new("HEAD is now at #{commit_hash}.", State::SUCCESS, current_head)
    else
      State.new("Commit #{commit_hash} does not exist.", State::ERROR)
    end
  end

  def branch
    @tree
  end

  def head
    if current_head.bucket.empty?
      State.new("Branch #{current_branch.name} does not have any commits yet.",
                State::ERROR)
    else
      State.new(current_head.message, State::SUCCESS, current_head)
    end
  end

  def get(name)
    if current_head.has_object? name
      State.new("Found object #{name}.", State::SUCCESS,
                  current_head.bucket[name])
    else
      State.new("Object #{name} is not committed.", State::ERROR)
    end
  end

  def log
    if current_branch.commits.empty?
      State.new("Branch #{current_branch.name} does not have any commits yet.",
                State::ERROR)
    else
      message = ""
      current_branch.commits.reverse_each do |hash, commit|
        message += "Commit #{commit.hash}\nDate: #{commit.date_str}\n\n\t"
        message += "#{commit.message}\n\n"
      end
      State.new(message.rstrip, State::SUCCESS)
    end
  end
end

repo = ObjectStore.init
repo.add("object1", "content1")
repo.add("object2", "content2")
repo.commit("So cool!")

p repo.remove("object1")
