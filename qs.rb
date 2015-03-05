#!/bin/ruby

def qs(arr)
  unless arr.length > 1
    return arr
  end
  return (qs arr.select { |e| e < arr[0] }) + (arr.select { |e| e == arr[0] }) + (qs arr.select { |e| e > arr[0] })
end

if __FILE__ == $PROGRAM_NAME
  print "Enter array elements: "
  arr = gets.chomp.split.map { |e| Integer(e) }
  puts qs arr
end
