#version 330 core

#define MAX_LIGHT_COUNT 8
#define LIGHT_POINT 0
#define LIGHT_DIRECTIONAL 1
#define LIGHT_SPOT 2

struct Light{
	int type;
	vec3 position;
	vec3 direction;
	vec3 color;
	float angle;

	float constant;
	float linear;
	float quadratic;
	float distance;
	float intensity;
};

struct Material
{
	sampler2D ambientTexture;
	vec3 ambientColor;
	int hasTexture;
};


uniform Material material;
uniform Light lights[MAX_LIGHT_COUNT];
uniform uint curLightCount;


uniform vec3 viewPos;

out vec4 FragColor;

in vec3 v_normal;
in vec3 v_position;
in vec2 v_textureCoords;

void main()
{
	vec3 diffuse;
	vec3 ambient;
	vec3 diffuseLight = vec3(0,0,0);
	if(material.hasTexture > 0)
	{
		vec4 textureimage = texture(material.ambientTexture, v_textureCoords);
		if (textureimage.a < 0.2)
			discard;
		diffuse = vec3(textureimage);
		ambient = diffuse;
	}
	else
	{
		diffuse = material.ambientColor;
		ambient = diffuse;
	}
	
	ambient *= 0.1;
	vec3 specular = vec3(0, 0, 0);

	
	for (int i = 0; i < MAX_LIGHT_COUNT; i++)
	{		
		if (lights[i].type == LIGHT_POINT)
		{
			float distance = length(lights[i].position - v_position);
			if (distance > lights[i].distance)
				continue;
			vec3 lightDir = normalize(lights[i].position - v_position);
			float diff = max(dot(lightDir, v_normal), 0.f);
		
			float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);
			diffuseLight += (lights[i].color * diff) * attenuation * lights[i].intensity;

		}
		else if (lights[i].type == LIGHT_DIRECTIONAL)
		{
			float diff = max(dot(-lights[i].direction, v_normal), 0.f);
			diffuseLight += (lights[i].color * diff) * lights[i].intensity;
		}
		else if(lights[i].type == LIGHT_SPOT) // SPOTLIGHT
		{
			float distance = length(lights[i].position - v_position);
			if (distance > lights[i].distance)
				continue;
			vec3 lightDir = normalize(lights[i].position - v_position);
			float theta = acos(dot(lightDir, normalize(-lights[i].direction)));
			if (lights[i].angle > theta)
			{
				float diff = max(dot(lightDir, v_normal), 0.f);

				float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);
				diffuseLight += (lights[i].color * diff) * attenuation * lights[i].intensity;
			}
				

		}
	}

	/*vec3 lightPos = { 0,0,5 };
	vec3 lightColor = {1,1,1};
	vec3 objectColor = { 0,1,0 };

	//diffuse
	vec3 lightDir = normalize(lightPos - v_position);
	float dif = max(dot(lightDir, v_normal), 0.f);
	vec3 diffuse = lightColor * dif;

	//specular
	vec3 viewDir = normalize(viewPos - v_position);
	vec3 reflectDir = reflect(-lightDir, v_normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.f), 512.f);
	vec3 specular = lightColor * spec;

	//spot
	vec3 direction = vec3(0, 0, -1);
	float cutOff = 0.1f;
	
	float theta = dot(lightDir, normalize(-direction));
	if (theta < cutOff)
		FragColor = vec4(1,1,1, 1.0);
	else
		FragColor = vec4(0, 0, 1, 1);*/

	vec3 difl = (diffuse * diffuseLight);

	FragColor = vec4(ambient + max(vec3(0,0,0),difl), 1.0f);


}