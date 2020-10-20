## 아직 평가하지 않은 Rating 예측

- 실제 값과 예측 값 비교
  - RMSE(Root Mean Square Error)
  
## 추천시스템을 평가하는 방법

- Utility Matrix에서 train data / test data 구분
- test data의 실제 값과 예측 값 비교
  - RMSE 재기
  - 상대적인 값 비교하기(두 벡터의 Correlation)
    - Pearson Correlation Coefficient
    - Spearman Correlation(실제 랭킹과 예측 랭킹 비교)
    - Rank Correlation(실제 랭킹과 예측 랭킹 비슷하면 점수 높이)
- Accuracy와 Diversity를 같이 높이는 것이 중요

## 협업필터링

- BaseLine Predictor를 이용한 협업필터링
  - 사용자 x가 아이템 i에 대해 매길 평점을 예측
  - b(xi) = u + b(x) + b(i)
  - r(xi) = b(xi) + weighted(r(xj)-b(xj))
    - 여기서 *에러를 최소화하는* Weight를 고르는 것이 중요

## Weight Learning in 협업필터링

- w(ij) = s(ij) / sum(s(ij))
- sum(r(xi)-r'(xi))^2 최소화
  - Gradient descent 기법
  
## Latent Factor Model

- 각 데이터를 n가지 latent factor space에 mapping시킴
  -> 나중에는 사용자도 mapping
  -> 이 space에서 사용자와 영화의 유사도를 구함.
  
- Matrix Factorization
  - R(users * items) = Q(users * factors) * P(T)(factors * items)
    - 여기서 Q = users를 잘 나타내는 row dimensional vector
    - 여기서 P(T) = items를 잘 나타내는 vector
  - How to Find R, Q, P(T)? : SVD(Singular Value Decomposition)
    - A = U * Sigma * V(T)
  - How to Find R, Q, P(T)? : 최적화
    - min(qx * pi - r(xi))^2 를 찾는다. by. Gradient Descent 기법
 
 ## Latent Factor Model의 확장 : Regularization( test 에러를 줄인다 )
 - Overfitting을 막는 방법임. 즉, Test 에러를 줄이는 방법임.
 - (실제 Rating - Q * P)^2 + Lambda 1 * Q + Lambda 2 * P
 
 
 ## Latent Factor Model의 확장 : Bias Modeling( bias와 interaction term을 분리한다 )
 - Before : directly modeling interaction
 > R(xi) = q(x) * p(i)
 - After : modeling bias and interaction
 > R(xi) = u + b(x) + b(i) + q(x)p(i)
  - 기본적인 bias와 차이나는 부분만 모델링하므로 더 잘 학습함.
  
 ## Latent Factor Model 확장판 최적화
 - min(u + b(x) + b(i) + q(x)p(i)) - r'(xi))^2 + lambda 1(qx) + lambda 2(pi) + lambda 3(bx) + lambda 4(bi)
 - 여러 파라미터를 Gradient Descent로 찾는다.
 
  
  Contents 기반 필터링
  
   
  collaborative filtering
    - memory based filtering
      - user based
      - item based
    - latent factor collaborative filtering
  
