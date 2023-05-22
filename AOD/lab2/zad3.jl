using JuMP
using GLPK

function main()
    # minimalna liczba radiowozów wymagana na dzielnicy p podczas zmiany s
    min_cars = [
    #    s1 s2  s3 
        [2, 4,  3], # p1
        [3, 6,  5], # p2
        [5, 7,  6]  # p3
    ]
    
    # maksymalna liczba radiowozów wymagana na dzielnicy p podczas zmiany s
    max_cars = [
    #    s1 s2  s3
        [3, 7,  5 ], # p1
        [5, 7,  10], # p2
        [8, 12, 10]  # p3
    ]

    # minimalna liczba radiowozów wymgana na zmianie
    shift_min = [10,20,18]
    # minimalna liczba radiowozów wymagna na dzielnicy
    p_min = [10,14,13]

    p_num = 3   # liczba dzielnic
    s_num = 3   # liczba zmian

solve_problem(min_cars, max_cars, shift_min, p_min, p_num, s_num)

end

function solve_problem(min_cars, max_cars, shift_min, p_min, p_num, s_num)
    
    model = Model(GLPK.Optimizer)
    # x[p,s] - liczba radiowozów na dzielnicy p podczas zmiany s
    @variable(model, min_cars[p][s] <= x[p = 1:p_num, s = 1:s_num] <= max_cars[p][s])    
    # Chcemy zminimalizować całkowitą liczbę radiowozów
    @objective(model, Min, sum(x[p,s] for p in 1:p_num, s in 1:s_num))
    # Liczba radiowozów na zmianie s nie może być mniejsza od minimalnej wymaganej liczby radowiozów na zmianie s
    @constraint(model, [s = 1:s_num], sum(x[p,s] for p in 1:p_num) >= shift_min[s])
    # Liczba radiowozów w dzielnicy p nie może być mniejsza od minimalnej wymaganej liczby radiowozów w dzielicy p
    @constraint(model, [p = 1:p_num], sum(x[p,s] for s in 1:s_num) >= p_min[p])

    optimize!(model)

    if termination_status(model) != OPTIMAL
        @warn("Nie znaleziono rozwiązania")
        return
    end

    @show objective_value(model)
    @show value.(x)
end

main()
