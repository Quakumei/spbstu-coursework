import random
import os

from tqdm import tqdm
import polars as pl
import numpy as np
from statsmodels.graphics.tsaplots import plot_acf
import matplotlib.pyplot as plt
import seaborn as sns

def rand():
    return random.uniform(0, 1)

def pseudo_randoms(n):
    return [rand() for _ in tqdm(range(n))]

def experiment(n):
    random_values = pseudo_randoms(n)
    return np.mean(random_values), np.std(random_values) ** 2, random_values

def deviations(a, b):
    return list(np.array(a) - np.array(b))

def autocorrelation_f(u, f):
    n = len(u)
    u_mean = np.mean(u)
    upper = ((u[i] - u_mean)*(u[i+f] - u_mean) for i in range(n-f))
    upper = np.sum(upper)
    lower = ((u[i] - u_mean) ** 2 for i in range(n))
    lower = np.sum(lower)
    return upper / lower

def main(seed, ns, lags):
    random.seed(seed)

    means, disps = [], []
    for n in ns:
        mean, disp, random_values = experiment(n)

        disps.append(disp)
        means.append(mean)

        # Построение графика корреллограммы
        plot_acf(random_values, lags=min(lags, n-1))
        os.makedirs(f'1/artefacts/{str(n)}', exist_ok=True)
        plt.savefig(f"1/artefacts/{str(n)}/correllogram_plot.png")
        plt.close()

        # Построение графика эмпирической интегральной функции распределения
        sns.displot(random_values, kind="ecdf")
        plt.axline((1, 1), slope=1, color='black', linestyle='--', alpha=0.3)
        plt.savefig(f"1/artefacts/{str(n)}/ecdf_plot.png")
        plt.close()

        # Построение графика эмпирической функции плотности распределения
        bin_count = 25
        sns.displot(random_values, bins=[i / bin_count for i in range(0, bin_count + 1)], stat="probability")
        plt.axhline(y=1/bin_count, color='black', linestyle='--', alpha=0.3)
        plt.savefig(f"1/artefacts/{str(n)}/pdf_plot.png")
        plt.close()


    means_awaited = [0.5 for m in means]
    disps_awaited = [0.08333 for disp in disps]

    means_deviations = deviations(means, means_awaited)
    disps_deviations = deviations(disps, disps_awaited)
    
    df = pl.DataFrame(
        {
            "n": ns,
            "mean": means,
            "mean_expected": means_awaited,
            "mean_deviation": means_deviations,
            "disp": disps,
            "disp_expected": disps_awaited,
            "disp_deviation": disps_deviations,
        }
    )
    print(df)

    # Сохранить таблицу в файл
    with open("1/artefacts/table.txt", "w") as f:
        print(df, file=f)


if __name__=='__main__':
    params = {
        "seed": 42,
        "ns": [10 ** i for i in range(1, 7)],
        "lags": 10,
    }
    main(**params)
