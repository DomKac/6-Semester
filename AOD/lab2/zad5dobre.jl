using JuMP
using GLPK

function main()

p_num = 4 # liczba produktów
m_num = 3 # liczba maszyn

min_to_produce = [
#    p1 p2 p3 p4
    [5, 3, 4, 4],   # M1
    [10,6, 5, 2],   # M2
    [6, 4, 3, 1],   # M3
]

# każda maszyna dostępna przez 60 godzin w tygodniu
m_min_limit = 60 * 60  
# cena sprzedaży każdego z produktów
product_price = [9, 7, 6, 5]
# koszt pracy maszyny przez 60 min
m_work_cost = [2, 2, 3]
# koszt materiału potrzebnego na wyrób produktu 
material_cost = [4, 1, 1, 1]
# popyt na produkt w tygodniu 
demand = [400, 100, 150, 500]

solve_problem(p_num, m_num, min_to_produce, m_min_limit,
                product_price, m_work_cost, material_cost, demand)
end


function solve_problem(p_num, m_num, min_to_produce, m_min_limit,
                        product_price, m_work_cost, material_cost, demand)
    model = Model(GLPK.Optimizer)

    # profit za 1kg produktu
    prod_profit = product_price .- material_cost

    # x[p] liczba wyprodukowanego produktu p
    @variable(model, 0 <= x[p = 1:p_num] <= demand[p], integer=true)

    # Maksymalizujemy zysk (sumujemy profity na każdym produkcie 
    # i odejmujemy koszt opłacenia maszyn)
    @objective(model, Max, 
        sum(x .* prod_profit) - sum(x[p] * min_to_produce[m][p] * m_work_cost[m] / 60 for m in 1:m_num, p in 1:p_num)
    )

    for m in 1:m_num
        @constraint(model, sum(x[p] * min_to_produce[m][p] for p in 1:p_num) <= m_min_limit)
    end

    # # println(model)
    optimize!(model)

    if termination_status(model) != OPTIMAL
        @warn("Nie znaleziono rozwiązania.")
        return
    end

    println("Maksymalny możliwy zysk: ")
    @show objective_value(model)

    println("Ile kg każdego produktu wyprodukowano: ")
    @show value.(x)
end

main()
