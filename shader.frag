#version 150

varying vec2 f_texcoord;
uniform sampler2D texture;

//lighting variables
uniform vec3 lightPos;

uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    
    // ambient lighting
    float ambientStrength = 0.4;
    vec3 ambient = ambientStrength * vec3(.5f,.4f,.3f);

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = .9 * diff * vec3(.9f,0.7f,.8f);
    

    // specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = .5 * spec * vec3(1,1,1);  

    vec4 Lighting = vec4((ambient + (diffuse + specular) * vec3(.4,.2,.5)),1.0f);

    gl_FragColor = Lighting * texture2D(texture, f_texcoord );


    // P1 Phosphor screen (Green monochrome) effect
    // fragColor = vec4( 0.0, 1.0, 0.0, 1.0 );

    // P2 Phosphor screen (Blue - green monochrome) effect
    // fragColor = vec4( 0.0, 1.0, 0.8, 1.0 );

    // P3 Phosphor screen (Amber monochrome) effect
    //gl_FragColor = vec4( 0.0, 1.0, 0.8, 1.0 );
    // P4 Phosphor screen (White monochrome) effect
    //gl_FragColor = vec4( 1.0, 1.0, 1.0, 1.0 );

    // P5 Phosphor screen (Black monochrome) effect
    // fragColor = vec4( 0.0, 0.0, 0.0, 1.0 );
}
