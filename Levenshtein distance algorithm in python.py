def levenshtein_distance(s1, s2):
    rows = len(s1) + 1
    cols = len(s2) + 1
    dist = [[0 for _ in range(cols)] for _ in range(rows)]

    for i in range(1, rows):
        dist[i][0] = i
    for j in range(1, cols):
        dist[0][j] = j

    for col in range(1, cols):
        for row in range(1, rows):
            if s1[row - 1] == s2[col - 1]:
                cost = 0
            else:
                cost = 1
            dist[row][col] = min(dist[row-1][col] + 1,      # deletion
                                 dist[row][col-1] + 1,      # insertion
                                 dist[row-1][col-1] + cost) # substitution
    return dist[rows - 1][cols - 1]
with open("input.txt", "r") as file:
    lines = file.readlines()
    num_inputs = len(lines) // 2  # Assuming each pair of lines represents one input
    for i in range(num_inputs):
        s1 = lines[i * 2].strip()
        s2 = lines[i * 2 + 1].strip()

        distance = levenshtein_distance(s1, s2)
        print("Levenshtein distance between '{}' and '{}' is: {}".format(s1, s2, distance))
