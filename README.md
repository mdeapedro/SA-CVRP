# SA-CVRP

Implementation of simulated annealing metaheuristic for the capacitated vehicle
routing problem (CVRP)

## Build

To build, run:

```sh
cmake . -B out/build
make -C out/build
```

Alternatively, run the [`build.sh`](build.sh) script.

## Instance file

The instance file shall be a text file formatted as following:

$$
\begin{matrix}
n      & k      & q                        \\
0      & 0      & w_{01} & \ldots & w_{0n} \\
c_1    & w_{10} & 0      & \ldots & w_{1n} \\
c_2    & w_{20} & w_{21} & \ldots & w_{2n} \\
\ldots                                     \\
c_n    & w_{n0} & w_{n1} & \ldots & 0      \\
\end{matrix}
$$

Where:

- $n$ is the number of nodes (customers + depot);
- $k$ is the number of vehicles;
- $q$ is the capacity of each vehicle;
- $w_{ij}$ is the minimum cost to travel from customer/depot $i$ to
  customer/depot $j$ ($w_{ij} = 0$ if $i = j$);
- $c_i$ is the demand of customer $i$;
- $c_i \ge 0$ is `int`;
- $0 \le u_j, v_j \le n$ is `int`;
- $w_j \ge 0$ is `float`;
- each customer is represented by an integer in $1, \ldots, n$;
- the depot is represented by $0$.

## Usage

```sh
sa_cvrp instance_filename time_limit_seconds
```
