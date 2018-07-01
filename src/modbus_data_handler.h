#ifndef MODBUS_DATA_HANDLER_H
#define MODBUS_DATA_HANDLER_H

#include "cpu_datatypes.h"
#include "modbus_element_base.h"
#include "modbus_element_array.h"



class MODBUS_DATA_HANDLER
{
    //Registered elements for COIL write and read
    MODBUS_ELEMENT_ARRAY ReadWriteElements;

    
    public:
    //The register options
    void register_coil_read_write(MODBUS_ELEMENT_BASE *pElement);

    bool8 write_coil(Uint8 BitNumber, bool8 Value);
    
    int read_coil(Uint8 EthernetRequest[]);

    int read_register(Uint8 EthernetRequest[]);

    private:
    void get_data(Uint8 EthernetRequest[], int StartAddress, int ByteDataLength);
};


#endif //MODBUS_DATA_HANDLER_H
