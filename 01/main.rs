use std::fs;

struct Number (String, usize);


fn main() {
    let filepath = "./input.txt";
    let input = fs::read_to_string(filepath).unwrap();

    let numbers: Vec<Number> = vec![
        Number(String::from("one"),   3,),
        Number(String::from("two"),   3,),
        Number(String::from("three"), 5,),
        Number(String::from("four"),  4,),
        Number(String::from("five"),  4,),
        Number(String::from("six"),   3,),
        Number(String::from("seven"), 5,),
        Number(String::from("eight"), 5,),
        Number(String::from("nine"),  4,),
    ];
    part1(input.clone());
    part2(input.clone(), &numbers);
}

#[allow(dead_code)]
fn part1(input: String) {
    let mut total_sum: usize = 0;

    for line in input.lines() {
        let (first_num, second_num) = get_first_and_last(line);
        let combined = first_num * 10 + second_num;
        total_sum += combined;
    }
    println!("part1: total_sum: {}", total_sum);
}

fn part2(input: String, numbers: &Vec<Number>) {
    let mut total_sum: usize = 0;

    for line in input.lines() {
        let (first_num, second_num) = get_first_and_last_with_word_support(line, numbers);
        let combined = first_num * 10 + second_num;
        total_sum += combined;
    }
    println!("part1: total_sum: {}", total_sum);
}

fn get_first_and_last_with_word_support(line: &str, numbers: &Vec<Number>) -> (usize, usize) {
    let mut first_num: usize = 0;
    let mut second_num: usize = 0;
    let line_len = line.len();
    for (i, ch) in line.chars().enumerate() {
        if is_digit(ch) {
            if first_num == 0 {
                first_num = ch as usize - '0' as usize;
                second_num = first_num;
            } else {
                second_num = ch as usize - '0' as usize;
            }
        } else {
            for (k, number) in numbers.iter().enumerate() {
                let end = if i + number.1 > line_len { line_len } else { i + number.1 };
                let slice = &line[i .. end];
                if slice == number.0 {
                    if first_num == 0 {
                        first_num = k + 1;
                        second_num = first_num;
                    } else {
                        second_num = k + 1;
                    }
                    break;
                }
            }
        }
    }
    return (first_num, second_num);
}

fn get_first_and_last(line: &str) -> (usize, usize) {
    let mut first_num: usize = 0;
    let mut second_num: usize = 0;
    for ch in line.chars() {
        if is_digit(ch) {
            if first_num == 0 {
                first_num = ch as usize - '0' as usize;
                second_num = ch as usize - '0' as usize;
            } else {
                second_num = ch as usize - '0' as usize;
            }
        }
    }
    return (first_num, second_num);
}


fn is_digit(ch: char) -> bool {
    return ch >= '0' && ch <= '9';
}

#[allow(dead_code)]
fn print_type_of<T>(_: &T) {
    println!("{0}", std::any::type_name::<T>());
}
