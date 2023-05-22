using JuMP
using GLPK

# liczba galonów w magazynie firmy
fuel_limit = [275000; 550000; 660000] 
# liczba galonów które potrzebuje lotnisko
fuel_needed = [110000; 220000; 330000; 440000]
# t_c[c,a] - koszt transportu 1 galonu paliwa z firmy c na lotnisko a
transport_cost = [10 10 9 11; 7 11 12 13; 8 14 4 9]
airp_num = 4
comp_num = 3

model = Model(GLPK.Optimizer)

# zmienne decyzyjne mają postać 
# x[i,j] - liczba galonów przesłanych z firmy c na lotnisko a
@variable(model, x[c = 1:comp_num, a = 1:airp_num] >= 0)
# Minimalizujemy koszt dostaw
@objective(model, Min, sum(x[c,a] * transport_cost[c,a] for c in 1:comp_num, a in 1:airp_num))
# Nie możemy wysłać z firmy więcej paliwa niż mamy w magazynie
@constraint(model, [c = 1:comp_num], sum(x[c,a] for a in 1:airp_num) <= fuel_limit[c])
# Musimy wysłać conajmniej tyle paliwa na lotnisko 'a' ile wynosi jego zapotrzebowanie
@constraint(model, [a = 1:airp_num], sum(x[c,a] for c in 1:comp_num) >= fuel_needed[a])

# println(model)
optimize!(model)
if termination_status(model) != OPTIMAL
    @warn("Nie znaleziono rozwiązania.")
    return
end
# println(solution_summary(model))
println("Minimalny koszt dostaw: ")
@show objective_value(model)

per_company_deliveries = [
    sum(
        value(x[i, airport]) 
        for airport in 1:4
    ) 
    for i=1:3
]

println("Liczba dostarczanego paliwa przez każdą z firm: ")
println(per_company_deliveries)
println("Firmy, które sprzedały całe paliwo: ")
println(per_company_deliveries .== fuel_limit)
4 
