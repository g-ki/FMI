def next_states(state):
    return [
        state.replace('>>_', '_>>', 1),
        state.replace('><_', '_<>', 1),

        state.replace('_<<', '<<_', 1),
        state.replace('_><', '<>_', 1),

        state.replace('>_', '_>', 1),
        state.replace('_<', '<_', 1),
    ]

def search_strategy(state, solution, visited = set(), path = list()):
    visited.add(state)
    path.append(state)
    if state == solution:
        return path

    for n_state in next_states(state):
        if n_state not in visited:
            result = search_strategy(n_state, solution, visited, path)
            if result is not None:
                return result

    path.pop()
    return None

# example:
# python frogs.py 2

if __name__ == '__main__':
    import sys
    size = (sys.argv[1] if len(sys.argv) > 1 else input())
    size = int(size)

    start_state = '>'*size + '_' + '<'*size
    end_state = '<'*size + '_' + '>'*size

    path = search_strategy(start_state, end_state)
    if path:
        for s in path:
            print(s)
    else:
        print("404: Solution not found!")
