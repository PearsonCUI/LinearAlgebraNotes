#include <stdio.h>
#include <iostream>
#include "mat3x3.h"
#include "vec3.h"
#include <vector>
#include <algorithm>

typedef struct
{
    vec3 miller;
    double resolution;
} Miller;


inline bool peak_greater_than_peak(Miller &a, Miller &b)
{
    return (a.resolution > b.resolution);   
}

int main(int argc, char **argv)
{
    if (argc < 7)
    {
		std::cout << "Argument number " << argc 
			<< " is not enough" << std::endl;		
        exit(0);
    }

        std::vector<double> dims;

	for (int i = 1; i < 7; i++)
	{
            double dim = atof(argv[i]);
            dims.push_back(dim);
	}
	
	mat3x3 real = mat3x3_from_unit_cell(&(dims[0]));
	mat3x3 mat = mat3x3_inverse(real);

        std::cout << "Your coordinate system is ";
        std::cout << std::endl;
        std::cout << mat3x3_desc(mat);
        std::cout << std::endl;

        std::vector<Miller> millers;

        std::cout << std::endl;

        for (int h = -5; h <= 5; h++) {
        for (int k = -5; k <= 5; k++) {
        for (int l = -5; l <= 5; l++) {
            
            vec3 miller = make_vec3(h, k, l);
            vec3 transformed = mat3x3_mult_vec(mat, miller);
            double length = vec3_length(transformed);
            double res = 1 / length;
	
	    Miller peak;
            peak.miller = miller;
            peak.resolution = res;
            millers.push_back(peak);
        }
        }
        }
        

        std::sort(millers.begin(), millers.end(), 
                  peak_greater_than_peak);

        int limit = 30;
        
        if (millers.size() < limit)
        {
            limit = millers.size();
        }
        
        for (int i = 0; i < limit; i++)
        {
	    Miller *miller = &millers[i];
            std::cout << vec3_desc(miller->miller) << " ";
            std::cout << "resolution: " << miller->resolution;
            std::cout << std::endl;
        }
}

