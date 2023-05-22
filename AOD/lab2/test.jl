using JuMP
using GLPK

model = Model(GLPK.Optimizer)

# @variable(model, x >= 0)
# @variable(model, 0 <= y <= 3)

# @objective(model, Min, 12x + 20y)

# @constraint(model, c1, 6x + 8y >= 100)
# @constraint(model, c2, 7x + 12y >= 120)

# print(model)

# optimize!(model)

# termination_status(model)

# print("objective_value(model): $(objective_value(model))")

# print("\nvalue(x): $(value(x))")

# print("\nvalue(y): $(value(y))")
# println();


product_price = [9, 7, 6, 5]
println(sum(product_price))

x = [
    [1,1,1,1],
    [1,1,1,1],
    [1,1,1,1]
]

min_to_produce = [
#    p1 p2 p3 p4
    [5, 3, 4, 4],   # M1
    [10,6, 5, 2],   # M2
    [6, 4, 3, 1],   # M3
]

m_num = 3
p_num = 4
m_work_time = zeros(m_num)

for m in 1:m_num
    sum = 0
    for p in 1:p_num
        sum = x[m][p] * min_to_produce[m][p]
    end
    m_work_time[m] = sum
end

m_work_time = [sum([x[m][p] * min_to_produce[m][p] for p in 1:p_num]) for m in 1:m_num]
println(m_work_time)
