using JuMP
using GLPK

function main()

    E = [
        # edge  C   T
        [(1,2), 5 , 5],
        [(1,3), 3 , 7],
        [(1,10),10, 1],
        [(2,3), 2 , 8],
        [(2,4), 6 , 4],
        [(2,5), 3 , 7],
        [(2,6), 3 , 7],
        [(3,4), 4 , 6],
        [(3,5), 4 , 6],
        [(3,6), 5 , 5],
        [(3,10),3 , 7],
        [(4,5) ,9 , 1],
        [(4,9) ,1 , 6],
        [(4,8) ,2 , 6],
        [(4,10),2 , 5],
        [(5,6) ,3 , 3],
        [(5,7) ,5 , 5],
        [(5,8) ,6 , 4],
        [(6,7) ,2 , 4],
        [(7,8) ,7 , 2],
        [(8,9) ,1 , 4],
        [(9,10),8 , 2]
    ]

    # utworzenie macierzy z samymi zerami
    n = 10
    c = zeros(n, n)
    t = zeros(n, n)

    # iteracja po krawędziach i aktualizacja macierzy
    for e in E
        u, v = e[1]
        c[u, v] = e[2]
        c[v, u] = e[2]
        t[u, v] = e[3]
        t[v, u] = e[3]
    end

    # ustawiamy źródło i ujście
    #    1  2  3  4  5  6  7  8  9  10 
    b = [1, 0, 0, 0, 0, 0, 0,-1, 0, 0]

    # Ustawiamy maksymalny czas
    T =  1000000

    solve_problem(n,c,t,b,T)
end

function solve_problem(n, c, t, b, T)
    model = Model(GLPK.Optimizer)

    @variable(model, 1 >= x[1:n, 1:n] >= 0)
    # @variable(model, x[1:n, 1:n], Bin)

    # Nie bierzemy pod uwagę krawędzi które nie istenieją
    # W grafie c i t te krawędzie mają wartość 0
    @constraint(model, [i = 1:n, j = 1:n; c[i, j] == 0], x[i, j] == 0)
    # Flow conservation constraint
    @constraint(model, [i = 1:n], sum(x[i, :]) - sum(x[:, i]) == b[i])
    # Całkowity czas podrózy nie może przekroczyć ustalonego T (maksymalnego czasu)
    @constraint(model, sum(t .* x) <= T)

    # Minimalizujemy łączny koszt podróży
    @objective(model, Min, sum(c .* x))

    # println(model)
    optimize!(model)

    if termination_status(model) != OPTIMAL
        @warn("Nie znaleziono rozwiązania.")
        return
    end

    @show objective_value(model)

    @show value.(x)
end

main()
