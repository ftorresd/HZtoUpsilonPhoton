std::pair<double,double> getMeanVariance(const std::vector<double>& vec) {
    double mean = 0,variance = 0, sum = 0, diffs = 0;

    size_t n = vec.size();
    for(size_t i = 0; i < n; ++i) {
        sum += vec[i];
    }
    mean = sum/((double)n);


    for(size_t i = 0; i < n; ++i) {
        diffs += pow(vec[i]-mean, 2);
    }
    variance = diffs/((double)(n-1));

    return std::make_pair(mean, variance);
}