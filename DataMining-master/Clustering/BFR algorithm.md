## BFR : k-means를 large data에 적용시 확장판
  가정: 1. cluster normally distributed
        2. euclidean space
        3. cluster=axis-aligned ellipses
        4. memory 는 O(clusters)에 비례, O(data)에 비례하는게 아님

  - Select initial K centroid
  - Point 를 세가지 종류로 나눌 수 있다.[DS/CS/RS]
    - Discard Set : centroid에 엄청 가까운 점들
      - N, SUM, SUMSQ
    - Compression Set : 지들끼리 가까운데 centroid하고는 먼 점들, cluster로 치진 않는다.
      - compute variance of subcluster(N, SUM, SUMSQ) : variance가 특정 파라미터보다 작으면 DS로 친다.
      - 마지막 round에서는 DS로 친다.
    - Retained Set : isolated 된 점들
  
  - Point들을 요약할 때 쓰이는 파라미터
    - Centroid = SUM(i)/N
    - Variance = (SUMSQ(i)/N)-(SUM(i)/N)^2
    
  - Pertubation Analysis
    - x1을 어떤 cluster에 넣을 것인가?
  
  - Mahalanobis Distance
    - normally distributed points일 때 euclidean distance로 측정할 때의 한계를 보완해준다.
    - parameter t보다 mahalanobis distance가 작으면 cluster로 친다.
