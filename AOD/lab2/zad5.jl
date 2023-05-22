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
    prod_profit = [product_price[i] - material_cost[i] for i in 1:p_num]

    # x[m,p] liczba wyprodukowanego produktu p przez maszyne m
    @variable(model, x[1:m_num, 1:p_num])

# czas pracy każdej z maszyn
    m_work_time = zeros(m_num)
    for m in 1:m_num
        sum_time = 0
        for p in 1:p_num
            sum_time += x[m,p] * min_to_produce[m][p]
        end
        m_work_time[m] = sum_time
    end
    # Maksymalizujemy zysk (sumujemy profity na każdym produkcie wywotrzonym przez każdą z maszyn 
    # i odejmujemy koszt opłacenia maszyn)
    @objective(model, Max, 
        sum(prod_profit[p] * x[m,p] - (m_work_time[m]/60) * m_work_cost[m]) for p in 1:p_num, m in 1:m_num)

    # żadna maszyna nie może pracować więcej niż 60h
    @constraint(model, [m = 1:m_num] ,m_work_time[m] <= m_min_limit)
    
    # nie możemy przekroczyć popytu na produkt
    @constraint(model, [p = 1:p_num] ,sum(x[:,p]) <= demand[p] )

    # # println(model)
    optimize!(model)

    if termination_status(model) != OPTIMAL
        @warn("Nie znaleziono rozwiązania.")
        return
    end

    @show objective_value(model)

    @show value.(x)
end

main()
