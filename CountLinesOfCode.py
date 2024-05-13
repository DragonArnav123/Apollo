import os

def count_lines_of_code(root_dir, file_extension):
    total_lines = 0
    results = []

    for dirpath, _, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith(file_extension):
                file_path = os.path.join(dirpath, filename)
                with open(file_path, 'r', encoding='utf-8') as file:
                    lines = file.readlines()
                    num_lines = len(lines)
                    total_lines += num_lines
                    results.append((os.path.relpath(file_path, root_dir), num_lines))

    return results, total_lines

def format_output(results, total_lines):
    formatted_results = "\n".join(f"{file_path}\t{num_lines}" for file_path, num_lines in results)
    return f"{formatted_results}\n\n{len(results)} files\t{total_lines} lines total"

if __name__ == "__main__":
    root_dir = os.getcwd()

    file_extension = []

    while True:
        file_extension.append(input("Enter the file extension (e.g., '.cpp'): "))
        print("To exit entering file extensions, enter -exit")

        if file_extension[len(file_extension) - 1] == "-exit":
            file_extension.pop()
            break

    results = []
    lines = 0

    for fe in file_extension:
        res, tl = count_lines_of_code(root_dir, fe)
        lines += tl
        output = format_output(res, tl)
        results.append(output)

    for r in results:
        print(r)

    print(f"Total Lines: {lines}")