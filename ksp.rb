#!/bin/ruby

def solve_knapsack(weights, profits, limit)
  prev = {0 => 0}
  best = 0
  0.upto weights.length - 1 do |i|
    # Copy last column across as a worst case scenario.
    curr = prev.dup

    # Check the last column and see if we can do better.
    prev.each do |weight, profit|
      tentative_weight = weight + weights[i]
      tentative_profit = profit + profits[i]
      if tentative_weight > limit
        next
      else
        best = [best, tentative_profit].max
      end
      if !prev.key? tentative_weight
        curr[tentative_weight] = tentative_profit
      elsif tentative_profit > prev[tentative_weight]
        curr[tentative_weight] = tentative_profit
      end
    end
    prev = curr
  end
  return best
end

if __FILE__ == $PROGRAM_NAME
  print "Enter weight limit: "
  max_weight = Integer gets.chomp
  print "Enter weights: "
  weights = gets.chomp.split.map { |e| Integer(e) }
  print "Enter profits: "
  profits = gets.chomp.split.map { |e| Integer(e) }
  if profits.length != weights.length
    puts "Error: Number of items must be the same in profits and weights."
  else
    puts solve_knapsack weights, profits, max_weight
  end
end
