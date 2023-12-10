import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator

def read_results_file(file_path):
    data = {'Optimization': [], 'Dataset': [], 'Average Time': [], 'Type': []}

    # Determine the type (my or lib) based on the file path
    file_type = 'my' if 'my' in file_path else 'lib'

    with open(file_path, 'r') as file:
        lines = file.readlines()
        i = 0
        while i < len(lines):
            if lines[i].startswith('Optimization:'):
                optimization = lines[i].split(',')[0].split(':')[1].strip()
                dataset = lines[i].split(',')[1].split(':')[1].strip()
                
                # Check if there are enough lines after Optimization
                if i + 1 < len(lines) and lines[i + 1].startswith('Average Time:'):
                    avg_time = float(lines[i + 1].split(':')[1].strip())
                    data['Optimization'].append(optimization)
                    data['Dataset'].append(dataset)
                    data['Average Time'].append(avg_time)
                    data['Type'].append(file_type)
                
                i += 2  # Skip additional lines to reach the next result
            else:
                i += 1

    return pd.DataFrame(data)

def plot_results(file_paths):
    dfs = []
    for file_path in file_paths:
        df = read_results_file(file_path)
        dfs.append(df)

    # Combine dataframes
    combined_df = pd.concat(dfs, axis=0, ignore_index=True)

    # Remove rows with non-numeric 'Average Time' values
    combined_df = combined_df[pd.to_numeric(combined_df['Average Time'], errors='coerce').notnull()]

    # Pivot the dataframe to have 'Type' as columns
    pivot_df = combined_df.pivot(index=['Dataset', 'Optimization'], columns='Type', values='Average Time').reset_index()

    ax = pivot_df.plot(kind='bar', x='Dataset', rot=0)

    # Set y-axis ticks with a step size of 0.01
    ax.yaxis.set_major_locator(MultipleLocator(0.003))

    # Rotate x-axis labels by 90 degrees
    plt.xticks(rotation=90)

    plt.title('Average Time for Different Optimizations and Datasets')
    plt.xlabel('Dataset')
    plt.ylabel('Average Time')
    plt.legend(title='Optimization Type', loc='upper left')
    plt.show()

def main():
    file_paths = ['results_summary_my.txt', 'results_summary_lib.txt']
    plot_results(file_paths)

if __name__ == "__main__":
    main()
