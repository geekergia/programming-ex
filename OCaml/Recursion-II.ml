let get_min a b =
    if a<b then a
    else b

let get_max a b =
    if a>b then a
    else b

let rec aux lates_left s a l min_len max_len = 
    if lates_left <= 0 then
        let total_count = 1 in
        let min_len = min_len in
        let max_len = max_len in
        (total_count, min_len, max_len) 
    else 
        let (count_a, min_a, max_a) = aux (lates_left - l) (s^"A") a l (String.length(s)+1) (String.length(s)+1) in
        let (count_l, min_l, max_l) = aux (lates_left - 1) (s^"L") a l (String.length(s)+1) (String.length(s)+1) in
        
        let (total_count:int) = (count_a + count_l) in
        let (min_len:int) =  get_min min_a min_l in
        let (max_len: int) =  get_max max_a max_l in
        (total_count, min_len, max_len)

let dropper a l =
    aux (a*l) "" a l 0 0;;

dropper 4 3;;