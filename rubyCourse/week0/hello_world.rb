#G.K hello_world.rb 06.10.2015

# add new line
print "Enter your name: "

user_name = gets.to_s

print "Hello, " + user_name

print "How old are you?\n => "

age = gets.to_i

if (age >= 18)
  puts "Get a driver license"
else
  puts "Go home"
end
