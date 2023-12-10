import os
import re

def extract_time_from_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
        match = re.search(r'\$\s+time:\s+(\d+\.\d+)', content)
        if match:
            return float(match.group(1))
    return None

def process_dataset(dataset_folder, optimization_flag, output_file):
    results = []

    for i in range(1, 101):
        file_path = os.path.join(dataset_folder, f"{i}.txt")
        if os.path.exists(file_path):
            result = extract_time_from_file(file_path)
            if result is not None:
                results.append(result)

    if results:
        avg_time = sum(results) / len(results)
        with open(output_file, 'a') as output:
            output.write(f"Optimization: {optimization_flag}, Dataset: {dataset_folder}\n")
            output.write(f"Average Time: {avg_time}\n\n")

def main():
    optimization_flags = ['-Og', '-O0', '-O1', '-O2', '-O3', '-Ofast']
    datasets = ['10000', '20000', '30000', '40000', '50000', '60000', '70000', '80000', '90000', '100000']
    output_file = 'results_summary_lib.txt'

    # Clear the existing contents of the output file
    open(output_file, 'w').close()

    for optimization_flag in optimization_flags:
        for dataset in datasets:
            dataset_folder = f"results_lib/out_{dataset}/{optimization_flag}"
            if os.path.exists(dataset_folder):
                process_dataset(dataset_folder, optimization_flag, output_file)

if __name__ == "__main__":
    main()
