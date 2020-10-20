## Motivation
	- how to visualize high dimensional points in 2-dim?
	- We want to understand its structure(angle, orientation, distance)

## Application
	- Distance -> Similarity
		- Cosine Distance ( sets as vectors) : angle!, -1~1
		- Jaccard Distance ( sets as sets) = 1-jaccard similarity
		- Euclidean Distance ( sets as points)
	
## Hard Point
	- Outliers
	- Boundary not vivid(not saparable)
	- High-dimensional spaces look different
	- 차원의 저주(Proportion of area decreases if dimension increases)
	- Example
		- Galaxies
		- Music CDs = Customers
		- Documents

## Methods of Clustering
### Hierarchical method
#### Bottom-up(Agglomerative)
	- each point is a cluster -> Merge
	- QUESTIONS
		1. How represent location?
			- Euclidean : CENTROID
			- Non-Euclieidean : closest point(clustroid : point중 하나라는 걸 명심!)
		2. How determine nearness?
			- Euclidean : Distance of CENTROID
			- Non-Euclieidean
				- Treat clustroid as Centroid
				- intercluster distance
				- measure cohesion
					- Diameter of merged cluster
					- Average distances btw points
					- Density (diameter or average distance/#)
		3. When stop?
			- 1. Number Predetermined
			- 2. When quality(average distance으로 결정) bad
			
				
#### Top-Down(Divisive)
	- One cluster -> Split
	
#### USAGE
	1. compute pairwise distance btw all pairs
	2. Merge ----- O(N^3).. O(N^2 logN)
				
### Point Assignment
	- maintain cluster -> merge 'near' cluster
