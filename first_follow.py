from collections import defaultdict

def compute_first(productions):
    first = defaultdict(set)
    
    def first_of(symbol):
        if symbol.islower() or not symbol.isalpha():  # Terminal symbol
            return {symbol}
        if symbol in first and first[symbol]:
            return first[symbol]
        for rule in productions[symbol]:
            for char in rule:
                first_set = first_of(char)
                first[symbol].update(first_set - {'ε'})
                if 'ε' not in first_set:
                    break
            else:
                first[symbol].add('ε')
        return first[symbol]
    
    for non_terminal in productions:
        first_of(non_terminal)
    return first

def compute_follow(productions, first):
    follow = defaultdict(set)
    start_symbol = next(iter(productions))  # Assuming the first non-terminal is the start symbol
    follow[start_symbol].add('$')
    
    def follow_of(non_terminal):
        for head, rules in productions.items():
            for rule in rules:
                for i, symbol in enumerate(rule):
                    if symbol == non_terminal:
                        if i + 1 < len(rule):
                            next_symbol = rule[i + 1]
                            follow_set = first[next_symbol]
                            follow[non_terminal].update(follow_set - {'ε'})
                            if 'ε' in follow_set:
                                follow[non_terminal].update(follow_of(head))
                        else:
                            if head != non_terminal:
                                follow[non_terminal].update(follow_of(head))
        return follow[non_terminal]
    
    for non_terminal in productions:
        follow_of(non_terminal)
    return follow

if __name__ == "__main__":
    # Example grammar
    productions = {
        'S': ['AB'],
        'A': ['aA', 'ε'],
        'B': ['bB', 'ε']
    }
    
    first = compute_first(productions)
    follow = compute_follow(productions, first)
    
    print("First sets:")
    for non_terminal, first_set in first.items():
        print(f"FIRST({non_terminal}) = {first_set}")
    
    print("\nFollow sets:")
    for non_terminal, follow_set in follow.items():
        print(f"FOLLOW({non_terminal}) = {follow_set}")
