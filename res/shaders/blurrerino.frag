uniform sampler2D texture;

void main() {
    float size = 1.f/600.f;
    vec4 originalColor = vec4(0,0,0,0);
    float total = 0.f;
    for(float i =-4.f; i <= 4.f; ++i) {
        for(float j =-4.f; j <= 4.f; ++j) {
            float radio = abs(i)+abs(j);
            if (radio <= 4.f) originalColor += 4.f*(8.f-radio)*texture2D(texture,vec2(gl_TexCoord[0].s+(size*i), gl_TexCoord[0].t+(size*j)));
            total += 4.f*(8.f-radio);
        }
    }

    vec4 final = originalColor / total;
    final = final+ 0.3f*texture2D(texture,vec2(gl_TexCoord[0].st));
    gl_FragColor = final*1.2f*gl_Color;
}
