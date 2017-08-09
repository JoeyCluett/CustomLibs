#ifndef __JJC__MAPNUM__H__
#define __JJC__MAPNUM__H__

float mapFloat(float input, float input_start, float input_end, float output_start, float output_end) {
    float output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
    return output;
}

double mapDouble(double input, double input_start, double input_end, double output_start, double output_end) {
    double output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
    return output;
}

float clampFloat(float input, float minimum, float maximum) {
    if(input > maximum)
        return maximum;

    if(input < minimum)
        return minimum;

    return input;
}

float absFloat(float f) {
    if(f < 0)
        return -1.0 * f;
    return f;
}

#endif // __JJC__MAPNUM__H__
