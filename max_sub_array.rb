#!/bin/ruby

def msa(arr)
  best = arr[0]
  curr = 0
  arr.each do |e|
    tentative_best = curr + e
    best = [best, tentative_best].max
    if tentative_best < 0
      curr = 0
    else
      curr += e
    end
  end
  return best
end

if __FILE__ == $PROGRAM_NAME
  print "Enter array elements: "
  arr = gets.chomp.split.map { |e| Integer(e) }
  puts msa arr
end
