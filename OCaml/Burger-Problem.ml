let rec dup count chr =
    if count <> 0 then
    chr ^ dup (count-1) chr
    else ""

let add_lettuce i dots width = 
    if i mod 3 = 1 then
    (dup dots ".") ^ (dup width "~") ^ "\n"
    else ""

let add_pickles i dots width = 
    if i mod 3 = 2 then
    (dup dots ".") ^ (dup width "o") ^ "\n"
    else ""

let add_top_bun dots width =
    (dup dots ".") ^ "/" ^ (dup (width - 2) "‾") ^ "\\" ^ "\n"

let add_bot_bun dots width =
    (dup dots ".") ^ "\\" ^ (dup (width - 2) "_") ^ "/" ^ "\n"

let add_patties_helper dots width = 
    (*string format of patties *)
    (dup dots ".") ^ (dup width "=") ^ "\n"

let rec add_patties dots width count = 
    (*multiples num of patties *)
    if count <> 0 then
    add_patties_helper dots width ^ add_patties dots width (count-1)
    else ""

let top_burger i dots width =
    (*adds all top components to make top bun *)
    let count = (i+1)/2 in
    add_top_bun dots width ^ add_lettuce i dots width ^ add_patties dots width count

let bot_burger i dots width = 
    (*adds all bot components to make bot bun*)
    let count = i/2 in 
    add_patties dots width count ^ add_pickles i dots width ^ add_bot_bun dots width

let rec burger_helper n i =
    (**recurses burger and defines values*)
    if n>=i then
    let dots = n-i in 
    let width = (2*i) + 3 in 
    top_burger i dots width ^ burger_helper n (i+1) ^ bot_burger i dots width
    else ""

let burger n =
    (**equivalent to burger(N) function*)
    burger_helper n 1