struct X_array
{
	int X <100>;
	int X_size;
};

struct Y_array
{
	int Y <100>;
	int Y_size;
};

struct XY_array
{
	int XY <200>;
	int XY_size;
};

struct ans
{
	float X_metre;
	int X_inter_product;
	float avg[2];	
};

struct r_times_X_Y
{
	int X_Y <100>;	
	int X_Y_size;
	float r;
};

struct rXY
{
	float prod <100>;
};

program ASK1_PROG1 {
		version ASK1_VERS {
			float metre(X_array) = 1;
			int inner_product(XY_array) = 2;
			float averageX(X_array) = 3;
			float averageY(Y_array) = 4;
			rXY product(r_times_X_Y) = 5;
			
	} = 1;
} = 0x12340000;
