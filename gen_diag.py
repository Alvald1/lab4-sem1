import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator

def read_results_file(file_path):
    data = {'Optimization': [], 'Dataset': [], 'Average Time': []}

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
                
                i += 2  # Skip additional lines to reach the next result
            else:
                i += 1

    return pd.DataFrame(data)

def plot_results(df):
    # Remove rows with non-numeric 'Average Time' values
    df = df[pd.to_numeric(df['Average Time'], errors='coerce').notnull()]
    
    pivot_df = df.pivot(index='Dataset', columns='Optimization', values='Average Time')
    ax = pivot_df.plot(kind='bar', rot=0)

    # Set y-axis ticks with a step size of 0.01
    ax.yaxis.set_major_locator(MultipleLocator(0.003))

    # Rotate x-axis labels by 90 degrees
    plt.xticks(rotation=90)

    plt.title('Average Time for Different Optimizations and Datasets')
    plt.xlabel('Dataset')
    plt.ylabel('Average Time')
    plt.legend(title='Optimization')
    plt.show()

def main():
    results_file = 'results_summary_lib.txt'
    df = read_results_file(results_file)
    plot_results(df)

if __name__ == "__main__":
    main()
