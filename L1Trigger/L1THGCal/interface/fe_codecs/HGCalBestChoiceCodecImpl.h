#ifndef __L1Trigger_L1THGCal_HGCalBestChoiceCodecImpl_h__
#define __L1Trigger_L1THGCal_HGCalBestChoiceCodecImpl_h__


#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "L1Trigger/L1THGCal/interface/HGCalTriggerGeometryBase.h"
#include "DataFormats/HGCDigi/interface/HGCDigiCollections.h"

#include <array>
#include <vector>


struct HGCalBestChoiceDataPayload
{
    static const size_t size = 116; 
    typedef std::array<uint32_t, size> trigger_cell_list; // list of trigger cell values
    trigger_cell_list payload;

    void reset() 
    { 
        payload.fill(0);
    }
};



class HGCalBestChoiceCodecImpl
{
    public:
        typedef HGCalBestChoiceDataPayload data_type;

        HGCalBestChoiceCodecImpl(const edm::ParameterSet& conf);

        std::vector<bool> encode(const data_type&) const ;
        data_type         decode(const std::vector<bool>&) const;  

        void linearize(const std::vector<HGCalDataFrame>&,
                std::vector<std::pair<DetId, uint32_t > >&);

        void triggerCellSums(const HGCalTriggerGeometryBase& ,
                const std::vector<std::pair<DetId, uint32_t > >&,
                data_type&);
        void bestChoiceSelect(data_type&);

        // Retrieve parameters
        size_t   nData()         const {return nData_;}
        size_t   dataLength()    const {return dataLength_;}
        double   linLSB()        const {return linLSB_;}
        double   adcsaturation() const {return adcsaturation_;}
        uint32_t adcnBits()      const {return adcnBits_;}
        double   tdcsaturation() const {return tdcsaturation_;}
        uint32_t tdcnBits()      const {return tdcnBits_;}
        double   tdcOnsetfC()    const {return tdcOnsetfC_;}
        uint32_t triggerCellTruncationBits() const {return triggerCellTruncationBits_;}
        uint32_t triggerCellSaturationBits() const {return triggerCellSaturationBits_;}


    private:
        size_t   nData_;
        size_t   dataLength_;
        size_t   nCellsInModule_;
        double   linLSB_;
        double   adcsaturation_;
        uint32_t adcnBits_;
        double   tdcsaturation_ ;
        uint32_t tdcnBits_ ;
        double   tdcOnsetfC_ ;
        double   adcLSB_;
        double   tdcLSB_;
        uint32_t triggerCellTruncationBits_;
        uint32_t triggerCellSaturationBits_;

};

#endif
