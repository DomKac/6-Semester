using JuMP
using GLPK

function main()

# Wymiary terenu
n = 6   # wiersze 
m = 10  # kolumny

k = 3   # odelgłość na którą widzi kamera

Containers = [
    (2, 1),
    (5, 2),
    (1, 4),
    (1, 7),
    (3, 7),
    (5, 8),
    (6, 10)
]

solve_problem(n,m,k,Containers)

end

function solve_problem(n, m, k, Containers)
    model = Model(GLPK.Optimizer)

    # stawiamy lub nie stawiamy kamery na polu x[i,j]
    @variable(model, x[1:n, 1:m], Bin)
    # Minimalizujemy liczbę postawionych kamer
    @objective(model, Min, sum(x))

    for cont in Containers
        # pobieramy wspórzędne kontenera
        ik, jk = cont[1], cont[2]
        # kamera nie może stać na polu z kontenerem
        @constraint(model, x[ik,jk] == 0)
        
        # obok kontenera musi znajdować się przynjamniej 1
        # kamera oddalona o maksymalnie k pól
        @constraint(model,
            sum(x[max(1, ik - d), jk] + # szukamy kamery nad kontenerem
                x[min(n, ik + d), jk] + # szukamy kamery pod kontenerem   
                x[ik, max(1, jk - d)] + # szukamy kamery na lewo od kontenera
                x[ik, min(m, jk + d)]   # szukamy kamery na prawo od kontenera
                for d in 1:k
                ) >= 1
        )
    end

    optimize!(model)

    if termination_status(model) != OPTIMAL
        @warn("Nie znaleziono rozwiązania")
        return
    end

    @show objective_value(model)
    @show value.(x)
end

main()
