use std::io;

fn main() {
    let mut t_str = String::new();
    io::stdin().read_line(&mut t_str).expect("Failed to read # test cases");
    let t: usize = t_str.trim().parse().expect("Failed to parse # test cases");

   for _ in 0..t {
        let mut n_str = String::new();
        io::stdin().read_line(&mut n_str).expect("Fail to read test case's size");
        let n: usize = n_str.trim().parse().expect("Failed to parse test case size");

        let mut c: Vec<f64> = Vec::with_capacity(n);
        let mut p: Vec<f64> = Vec::with_capacity(n);
        for _ in 0..n {
            let mut line = String::new();
            io::stdin().read_line(&mut line).expect("Failed to read test case");
            let parts: Vec<f64> = line
                .trim()
                .split_whitespace()
                .map(|s| s.parse::<f64>().unwrap())
                .collect();
            c.push(parts[0]);
            p.push(parts[1]);
        }
        // dp[i] = max reward starting with stamina 1
        // recursive structure: dp[i] = max {c[i] + (1-p[i]/100)dp[i+1], dp[i+1]}
        let mut dp: Vec<f64> = vec![0.0;n];
        dp[n-1] = c[n-1];
        for i in (0..n-1).rev() {
            let option1: f64 = dp[i + 1];
            let option2: f64 = c[i] + (1.0 - p[i]/100.0) * dp[i+1];
            dp[i] = f64::max(option1, option2);
        }
        println!("{}", dp[0]);
    }
}
