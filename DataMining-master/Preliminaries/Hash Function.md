# Good Hash Function?

## Simple Uniform Hash
  - 계산된 해쉬들이 0~Bucket#-1 까지의 범위를 같은 확률로 골고루 나타낼 것
  
  - 각각의 해쉬값들은 서로 연관성 없이 독립적으로 생산될 것
  
## Division Method
  - ex. H(x) = x mod B (단, B= #of buckets)
  
    - Bucket number를 구할 때 조심할 점
