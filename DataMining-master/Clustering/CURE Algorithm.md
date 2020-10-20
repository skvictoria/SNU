## CURE Algorithm : Extension of k-means (arbitrary shape 일 때)

### BFR/k-means의 한계
- 가정의 한계 : cluster normally distributed
- 가정의 한계 : axes fixed

### Algorithm : 2-pass
- First Pass
  - 1. pick random sample(main memory 크기만큼)
  - 2. initial clusters
  - 3. representative points
    - pick remote points for each cluster
    - shrink representatives by 20%
  - 4. merge clusters
  
- Second Pass
  - 1. rescan whole dataset & visit each point
  - 2. place it in the closest cluster
