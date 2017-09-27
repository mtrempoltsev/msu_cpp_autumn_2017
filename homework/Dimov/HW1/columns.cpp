#define SIZE 10000
double a[SIZE][SIZE];
int i;

int main( int argc, char **argv )
{
  int j;
  int s = 0;
  for( j = 0; j < SIZE; j++ )
  {
    for( i = 0; i < SIZE; i++ )
    {
      s += a[i][j];
    }
  }
}
