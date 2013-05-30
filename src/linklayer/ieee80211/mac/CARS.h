/*
 * CARS.h
 *
 *  Created on: 17 May 2013
 *      Author: kenneth Nwizege
 */

#ifndef CARS_H_
#define CARS_H_
#include <math.h>

class CARS {
public:
    CARS();

    //Methods to be called so as to initialize parameter at the beginning
    void setUpdateInterval(double val);//Update interval in ms
    void setMaxRetransmissions(long a);

    double getBitRate(double speed,long len);//select and return the BitRate to be  used to transmit Packets

    double getAlpha(double speed);

    //Methods Regarding E_C
    double ec(double speed,double rate, long len);//context informations distance is set via updateDistance() method, so it is not passed as parameter.
    void setFirstPER(double val, double rate);//val = PER, rate = p band rate in Mbps
    void setCurrentPER(double val, double rate);//val = PER, rate = p band rate in Mbps

    void updatePositions(double speed1,double angle1, double speed2, double angle2);//Update Positions of Vehicles using speed and angles; speed is in meters per second (ms^-1) and angles  in degrees
    void setPositions(double px1, double py1, double px2, double py2);//Directly updating  positions

    void setNoRetransmissions(int val);

    //Methods Regarding E_C
    double eh(double rate, long len);

    CARS(const CARS& orig);
    virtual ~CARS();
private:
    double update_interval;//Update interval in ms (milliseconds)
    long N; //the maximum number of retransmissions
    int sigma; //weight that signifies the penalty given to unsuccessful packet transmission
    double first_PER, previous_PER;
    double previous_distance, previous_bitrate;
    double current_distance;
    double x1,y1,x2,y2;
    int no_retransmissions;
    double previous_rate;
    double p_band_rates[8];
    double last_PERs[8][10];//Last 10 PERs of each data rate
    int no_last_PERs[8];//Available amount of data PER per each rate

    void insertNewPER(int index, double val);//index refers to the p band data rate
    int getTotal(int val);//this return value = (2^val) + (2^(val-1)) + (2^(val-2)) + ... + 2^2 + 2^1
    double getCumulativeTotal(int index,int val);
    double getTotalAverage();//In initial situations this method has to be called,in order to get PER depending on past data
    double updateDistance();
};

#endif  /* CARS_H */

