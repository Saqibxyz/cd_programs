def display_productions(productions):
    for non_terminal, rules in productions.items():
        for rule in rules:
            print(f"{non_terminal} -> {rule}")

# Function to convert non-deterministic grammar to deterministic grammar using left factoring
def convert_to_deterministic(productions):
    deterministic_productions = {}
    for non_terminal, rules in productions.items():
        common_prefix = rules[0]
        for rule in rules:
            common_length = 0
            while (common_length < len(common_prefix) and
                   common_length < len(rule) and
                   common_prefix[common_length] == rule[common_length]):
                common_length += 1
            common_prefix = common_prefix[:common_length]
        
        if len(rules) > 1 and common_prefix:
            new_non_terminal = non_terminal + "'"
            deterministic_productions[non_terminal] = [common_prefix + new_non_terminal]
            deterministic_productions[new_non_terminal] = [rule[len(common_prefix):] or 'ε' for rule in rules]
        else:
            deterministic_productions[non_terminal] = rules
    return deterministic_productions

# Main program
if __name__ == "__main__":
    productions = {
        'S': ['ab', 'abc', 'a'],
        'A': ['b', 'bc']
    }

    print("Original Grammar:")
    display_productions(productions)

    deterministic_productions = convert_to_deterministic(productions)

    print("\nDeterministic Grammar:")
    display_productions(deterministic_productions)
