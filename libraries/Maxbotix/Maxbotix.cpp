#include "Maxbotix.h"

Maxbotix::Maxbotix(uint8_t pin, MAXBOTIX_INPUT_t input, MAXBOTIX_MODEL_t model, MAXBOTIX_FILTER_t filter,
                   uint8_t sample_size) :
        pin(pin), input(input), model(model), filter(filter), sample_size(sample_size) {
    pinMode(pin, INPUT);
    init();
}

void Maxbotix::init() {
    switch (filter) {
        case MEDIAN:
        case HIGHEST_MODE:
        case LOWEST_MODE:
        case BEST:
            if (sample_size == 0) sample_size = 5;
            else if (sample_size % 2) sample_size++;
            break;

        case SIMPLE:
            if (sample_size == 0) sample_size = 2;
            break;

        case NONE:
        default:
            sample_size = 1;
            break;
    }

    sample = new float[sample_size];
}

Maxbotix::~Maxbotix() {
    delete[] sample;
    delete serial;
}

float Maxbotix::getRange() {
    float range;

    readSample();

    switch (filter) {
        case MEDIAN:
            range = getSampleMedian();
            break;

        case HIGHEST_MODE:
            range = getSampleMode(true);
            break;

        case LOWEST_MODE:
            range = getSampleMode(false);
            break;

        case SIMPLE:
            while (sample[0] != sample[sample_size - 1])
                pushToSample(readSensor());

            range = sample[0];
            break;

        case BEST:
            range = getSampleBest();
            break;

        case NONE:
        default:
            range = sample[0];
            break;
    }

    return range;
}

float Maxbotix::getSampleMedian() {
    return sample[sample_size / 2];
}

float Maxbotix::getSampleMode(bool highest) {
    float mode = sample[0];
    uint8_t mode_count = 1;
    uint8_t count = 1;

    for (int i = 1; i < sample_size; i++) {
        if (sample[i] == sample[i - 1]) count++;
        else count = 1;

        if (sample[i] == mode) {
            mode_count++;
        } else if (!highest && count > mode_count || highest && count == mode_count) {
            mode_count = count;
            mode = sample[i];
        }
    }

    return mode;
}

float Maxbotix::getSampleBest() {
    float range;

    if ((range = getSampleMode(true)) != getSampleMode(false))
        range = getSampleMedian();

    return range;
}

float Maxbotix::readSensor() {
    float result;

    switch (input) {
        case PW:
            switch (model) {
                case LV:
                    result = toCentimeters(pulseIn(pin, HIGH) / 147.0);
                    break;

                case XL:
                    result = pulseIn(pin, HIGH) / 58.0;
                    break;

                case HRLV:
                    result = pulseIn(pin, HIGH) / 10.0;
                    break;

                default:
                    break;
            }

            break;

        case AN:
            switch (model) {
                case LV:
                    result = toCentimeters(analogRead(pin) / 2.0);
                    break;

                case XL:
                    result = analogRead(pin);
                    break;

                case HRLV:
                    result = analogRead(pin) * 5.0 / 10.0;
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }

    return result;
}

void Maxbotix::readSample() {
    // read
    for (int i = 0; i < sample_size; i++) {
        sample[i] = readSensor();

        if (input == AN && i != sample_size - 1)
            delay(ad_sample_delay);
    }

    // sort
    sortSample();
}

void Maxbotix::pushToSample(float value) {
    for (int i = 0; i < sample_size - 1; i++)
        sample[i] = sample[i + 1];

    sample[sample_size - 1] = value;
}


void Maxbotix::sortSample() {
    for (int i = 1; i < sample_size; i++) {
        float j = sample[i];
        int k;

        for (k = i - 1; (k >= 0) && (j < sample[k]); k--)
            sample[k + 1] = sample[k];

        sample[k + 1] = j;
    }
}
