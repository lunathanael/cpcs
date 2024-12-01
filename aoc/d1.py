def process_pairs(filename):
    # Read pairs from file
    v1, v2 = [], []
    with open(filename, 'r') as f:
        for line in f:
            # Split each line into two numbers
            n1, n2 = map(int, line.strip().split())
            v1.append(n1)
            v2.append(n2)
    
    # Count frequencies in each list
    v2_freq = {}
    for num in v2:
        v2_freq[num] = v2_freq.get(num, 0) + 1
    result = 0
    for num in v1:
        result += num * v2_freq.get(num, 0)
    
    return result

# Example usage
if __name__ == "__main__":
    result = process_pairs("input.txt")
    print(f"Similarity score: {result}")
