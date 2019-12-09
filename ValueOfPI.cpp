#include<mpi.h>
#include<cassert>
#include<random>
#include<iomanip>
#define DEFAULT_ITERATIONS_COUNT 1000
#define LOOPS_IN_ITERATION 100000
#define TASK_TAG 1024
using namespace std;
mt19937 mt_engine;
uniform_real_distribution<double> real_distribution;
long calculate_hits(int iterations);
void perform_process(long total_iterations, int curr_rank, int world_size);
int main(int argc, char* argv[]){
 long total_iterations = 0;
 if (argc == 2){
 char *input = argv[1];
 total_iterations = strtol(input, NULL, 10);
 }
 if (total_iterations == 0){
 total_iterations = DEFAULT_ITERATIONS_COUNT;
 }
 random_device rd;
 mt_engine.seed(rd());
 MPI_Init(&argc, &argv);
 double tic = MPI_Wtime();
 int world_size;
 MPI_Comm_size(MPI_COMM_WORLD, &world_size);
 int curr_rank;
 MPI_Comm_rank(MPI_COMM_WORLD, &curr_rank);
 perform_process(total_iterations, curr_rank, world_size);
 double toc = MPI_Wtime();
 MPI_Finalize();
 if (curr_rank == 0){
 printf("--- Operation took %f seconds ---\n", (toc - tic));
 system("pause");
 }
 return 0;
}
void perform_process(long total_iterations, int curr_rank, int world_size){
 printf( "[Node #%d] Starting process of calculating pi value.\n", curr_rank);
 int *iterations_distribution = new int[world_size];
 if (curr_rank == 0){
 int iterations_left = total_iterations;
 int iterations_per_worker = total_iterations / world_size;
 for (int i = 0; i < world_size - 1; i++)
 {
 iterations_distribution[i] = iterations_per_worker;
 iterations_left -= iterations_per_worker;
 }
 iterations_distribution[world_size - 1] = iterations_left;
 printf("[Node #0] Base nodes iterations: %d last node: %d\n",iterations_per_worker,
iterations_left);
 }
 int iterations;
 MPI_Scatter(iterations_distribution, 1, MPI_INT, &iterations, 1, MPI_INT, 0,
MPI_COMM_WORLD);
 printf("[Node #%d] Got %d iterations to perform.\n",curr_rank,iterations);
 long long total_hits = 0;
 for (int i = 0; i < iterations; i++)
 {
 int result = calculate_hits(LOOPS_IN_ITERATION);
 total_hits += result;
 if (curr_rank == 0 && i % 256 == 0)
 {
 printf("[Node #0] %d done\n",(100 * i) / iterations);
 }
 }
 long long *received_hits = new long long[world_size];
 MPI_Gather(&total_hits, 1, MPI_LONG_LONG, received_hits, 1, MPI_LONG_LONG,
0, MPI_COMM_WORLD);
 if (curr_rank == 0)
 {
 long long total_received_hits = 0;
 for (int i = 0; i < world_size; i++)
 {
 total_received_hits += received_hits[i];
 }
 double total_attempts = (double)total_iterations * LOOPS_IN_ITERATION;
 double pi_value = (double)total_received_hits * 4.0 / total_attempts;
 printf("[Node #0] Received %lld received hits in %f attempts.\n", total_received_hits,
total_attempts);

 printf("[Node #0] Calculated PI value is %f\n",pi_value);
 printf("[Node #0] Difference is %f\n\n",3.14159265358979323846 - pi_value);
 }
 printf("[Node # %d] dies.\n",curr_rank);
 delete[] iterations_distribution;
 delete[] received_hits;
}
long calculate_hits(int iterations)
 {
 int i;
 int hits = 0;
 for (i = 0; i < iterations; i++)
 {
 double x = (double)real_distribution(mt_engine);
 double y = (double)real_distribution(mt_engine);
 if (x * x + y * y <= 1.0)
 {
 hits++;
 }
 }
 return hits;
 }