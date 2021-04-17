let rec f a b = 
    if a=0 && b=0 then 1
    else if a=0 || b=0 then 0 
    else f (a-1) (b-1) + b * f (a-1) b ;;

let rec count a b n k sum = 
    if a=n && b=k then sum 
    else  
        if b<k then count a (b+1) n k (sum + f a b)
        else count (a+1) 0 n k (sum + f a b) ;;

let g n k =
    count 0 0 n k 0 ;;

g 14 15;;

