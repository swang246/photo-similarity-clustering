# Photo Similarity Clustering

A C++ project that groups photos based on pairwise similarity scores using a maximum-spanning-tree-based clustering approach and the Union-Find data structure.

## Overview

This project organizes 20 photos into three groups based on their similarity scores. It processes photo pairs from highest to lowest similarity and uses Union-Find to merge connected photos while tracking the number of groups.

## How It Works

1. **Represent photo similarities:** Store photo pairs and their similarity scores as weighted edges in a graph.
2. **Sort edges:** Sort the edges in descending order of similarity.
3. **Initialize Union-Find:** Start with each photo in its own group.
4. **Merge groups:** Process edges from highest to lowest similarity and use Union-Find to merge separate groups.
5. **Form clusters:** Stop merging when three groups remain and collect photos according to their connected components.
6. **Measure runtime:** Record the execution time of the clustering process.

### Compile

```bash
g++ photo_clustering.cpp -o photo_clustering
```

### Run

**Windows (PowerShell):**

```powershell
.\photo_clustering
```

**Linux / macOS:**

```bash
./photo_clustering
```

The program prints the three resulting photo groups and the measured runtime.

## Input Data

The current implementation uses a predefined set of 20 photo identifiers and weighted similarity scores. Each edge represents a pair of photos and their similarity.

## Purpose

This project explores graph-based clustering and efficient set management through a practical example of grouping photos by similarity.
