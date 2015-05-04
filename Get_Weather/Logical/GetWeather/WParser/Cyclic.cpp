
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif


#include "jansson.h"

void _CYCLIC ProgramCyclic(void)
{

	if( response_JSON_valid) {
		response_JSON_valid = 0;
		
		//init structure
		json_t *root;
		json_error_t error;
		root = json_loads(response_JSON, 0, &error);		
		
		if( root) {
			//parse
			/*
			{
			"coord":{"lon":17.75,"lat":48.61},
			"sys":{"message":1.7319,"country":"Slovakia","sunrise":1430623518,"sunset":1430676384},
			"weather":[{"id":500,"main":"Rain","description":"light rain","icon":"10d"}],
			"base":"stations",
			"main":{
			."temp":284.817,
			."temp_min":284.817,
			."temp_max":284.817,
			."pressure":994.66,
			."sea_level":1028.88,
			."grnd_level":994.66,
			."humidity":75},
			"wind":{"speed":3.27,"deg":160.002},
			"clouds":{"all":92},
			"rain":{"3h":0.185},
			"dt":1430646855,
			"id":3056697,
			"name":"Krakovany",
			"cod":200
			}
			*/
			
			json_t *jmain=json_object_get( root,"main");
			r1=json_unpack(jmain,"{s:F}","temp",&p_temp);
			r2=json_unpack(jmain,"{s:F}","humidity",&p_humidity);
			
			json_t *jwind=json_object_get( root,"wind");
			r3=json_unpack(jwind,"{s:F}","speed",&p_wind_speed);
			r4=json_unpack(jwind,"{s:F}","deg",&p_wind_deg);
			
			json_t *jclouds = json_object_get( root,"clouds");
			r5=json_unpack(jclouds,"{s:F}","all",&p_clouds);
			
			//free			
			json_decref(root);
			
			if( r1+r2+r3+r4+r5 == 0) {
				weather.temp = p_temp;
				weather.clouds = p_clouds;
				weather.wind_dir = p_wind_deg;
				weather.wind_speed = p_wind_speed;
				weather.humidity = p_humidity;
				weather.isValid = 1;
			} else {
				weather.isValid = 0;
			}
		} else { //root not found
			weather.isValid = 0;
		}
	}
}
