macro_rules! readints {
    () => {{
        let mut s = String::new();
        std::io::stdin().read_line(&mut s).unwrap();
        s.split_whitespace().map(|x| x.parse().unwrap()).collect::<Vec<usize>>()
    }};
}

macro_rules! readint {
    () => {{
        let mut n_str = String::new();
        std::io::stdin().read_line(&mut n_str).unwrap();
        n_str.trim().parse().unwrap()   
    }};
}

struct SparseTable<'a> {
    log: Vec<usize>,
    table: Vec<Vec<usize>>,
    arr: &'a [usize],
}

impl<'a> SparseTable<'a> {
    fn new(arr: &'a [usize]) -> Self {
        let n = arr.len();
        let k = n.ilog2() as usize + 1;
        
        let mut log = vec![0; n + 1];
        for i in 2..=n {
            log[i] = log[i / 2] + 1;
        }
        
        let mut table = vec![vec![0; k]; n];
        for i in 0..n {
            table[i][0] = i;
        }
        
        for j in 1..k {
            let mut i = 0;
            while i + (1 << j) <= n {
                let left_idx = table[i][j - 1];
                let right_idx = table[i + (1 << (j - 1))][j - 1];
                table[i][j] = if arr[left_idx] >= arr[right_idx] {
                    left_idx
                } else {
                    right_idx
                };
                i += 1;
            }
        }
        
        SparseTable { log, table, arr }
    }
    
    fn query(&self, l: usize, r: usize) -> usize {
        let j = self.log[r - l + 1];
        let left_idx = self.table[l][j];
        let right_idx = self.table[r + 1 - (1 << j)][j];
        if self.arr[left_idx] >= self.arr[right_idx] {
            left_idx
        } else {
            right_idx
        }
    }
}

/*
    Solver: consider an array a[0...n-1]
    Find a[peak] that is the max. value in a.
    - Note that unless this peak is leftmost or rightmost, we must get rid of elements to the left or right of a[peak] at some point.
        Exercise: show that it never just hurts to get rid of these elements at the beginning.
    - Next, we need to decide if we need to get rid of the elements to the left or right of a[peak]
        If we decide to get rid of the elements to the left, the cost is (peak-1) + solver(a[peak+1..n-1])
        If we decide to get rid of the elements to the right, the cost is (n-1-peak) + solver(a[0..peak-1])
        Recursively solve the 2 sides.
    - To find the max value efficiently, we precompute a sparse table of the original array beforehand.
*/
fn solver(a: &[usize], st: &SparseTable, l_idx: usize, r_idx: usize) -> usize {
    // base case.
    if l_idx >= r_idx {
        return 0;
    }

    if r_idx - l_idx + 1 <= 2 {
        return 0;
    }
    
    let peak = st.query(l_idx, r_idx);
    
    if peak == l_idx {
        return solver(a, st, peak + 1, r_idx);
    } else if peak == r_idx {
        return solver(a, st, l_idx, peak - 1);
    }

    let cost_left = (peak - l_idx) + solver(a, st, peak + 1, r_idx);
    let cost_right = (r_idx - peak) + solver(a, st, l_idx, peak - 1);
    std::cmp::min(cost_left, cost_right)
}

fn main() {
    let mut t: usize = readint!();
    while t > 0 {
        let n: usize = readint!();
        let a: Vec<usize> = readints!();
        let st = SparseTable::new(&a);
        let res = solver(&a, &st, 0, n - 1);
        println!("{}", res);
        t -= 1;
    }
}