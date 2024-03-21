# peKNN
A more efficient KNN architecture.

This repo is an implementation of the short paper, "peKNN: A more efficient KNN architecture".

You can see the mini-paper [here](https://kendasi.com/peknn_paper.pdf).

## Usage
KNN (K-nearest neighbor) is an incredibly powerful yet simple model algorithm which simply finds the most similar inputs in training data and returns it's matching outputs, often avoiding issues such as overfitting. However, KNN is also incredibly inefficient, as it has to calculate the distance from each and every training example.

peKNN (Pre-Elimination KNN) is an architecture of KNN which is optimised to be approximately 20% faster on average. It does this by first calculating the distance from every training example with a simpler, less effective algorithm, removing the ones that are far away, and only calculating with more resource-intensive algorithms the closer ones.

This project has a basic implementation of peKNN with 2-dimensional inputs, with K set to the square root of the number of training examples, and P set to half of the number of training examples. It isn't adjustable at the moment, it simply times the outputs for comparison.

## Installation
To install peKNN, first clone the repo and enter the directory:
```
git clone https://github.com/jakeSteinburger/peKNN
cd peKNN
```
You'll need to first have Git installed. Next, compile the main file:
```
g++ peknn_and_timer.cpp
```
You'll need to have g++ installed. You can then run the test model like so:
```
./a.out
```
This will return some random colours (outputs of the model) and the times for the optimised and the normal KNN models.

## Timings
You'll find in this repo a file, `times.txt`, which contains some sample times for the models. I've already run the models a few times (on Google Colab servers), and these are the results I've gotten. You can see the average times at the bottom of the file.

## License
This project has no license, so you're free to use the code, project, and theory however you like.
