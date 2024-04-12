/* File:     caPutJsonLogShellCommands.cpp
 * Author:   Matic Pogacnik
 * Created:  21.07.2020
 *
 * Contains code for a IOC shell configuration commands of the
 * JSON CA put logger implementation.
 *
 * Modification log:
 * ----------------
 * v 1.0
 * - Initial version
*/

#include <errlog.h>
#include <iocsh.h>
#include <epicsExport.h>
#include <string>

#include "caPutJsonLogTask.h"

/* EPICS iocsh shell commands */
extern "C"
{
    extern int caPutLogJsonMsgQueueSize;

    /* Initalisation */
    int caPutJsonLogInit(const char * address, caPutJsonLogConfig config){
        CaPutJsonLogTask *logger =  CaPutJsonLogTask::getInstance();
        if (logger != NULL) return logger->initialize(address, config);
        else return -1;
    }

    static const iocshArg caPutJsonLogInitArg0 = {"address", iocshArgString};
    static const iocshArg caPutJsonLogInitArg1 = {"config", iocshArgInt};
    static const iocshArg *const caPutJsonLogInitArgs[] = {
        &caPutJsonLogInitArg0,
        &caPutJsonLogInitArg1
    };
    static const iocshFuncDef caPutjsonLogInitDef = {"caPutJsonLogInit", 2, caPutJsonLogInitArgs};
    static void caPutJsonLogInitCall(const iocshArgBuf *args)
    {
        caPutJsonLogInit(args[0].sval, static_cast<caPutJsonLogConfig>(args[1].ival));
    }


    /* Reconfigure */
    int caPutJsonLogReconf(caPutJsonLogConfig config){
        CaPutJsonLogTask *logger =  CaPutJsonLogTask::getInstance();
        if (logger != NULL)  return logger->reconfigure(config);
        else return -1;
    }

    static const iocshArg caPutJsonLogReconfArg0 = {"config", iocshArgInt};
    static const iocshArg *const caPutJsonLogReconfArgs[] = {
        &caPutJsonLogReconfArg0
    };
    static const iocshFuncDef caPutJsonLogReconfDef = {"caPutJsonLogReconf", 1, caPutJsonLogReconfArgs};
    static void caPutJsonLogReconfCall(const iocshArgBuf *args)
    {
        caPutJsonLogReconf(static_cast<caPutJsonLogConfig>(args[0].ival));
    }

    /* Report */
    int caPutJsonLogShow(int level){
        CaPutJsonLogTask *logger =  CaPutJsonLogTask::getInstance();
        if (logger != NULL)  return logger->report(level);
        else return -1;
    }

    static const iocshArg caPutJsonLogShowArg0 = {"level", iocshArgInt};
    static const iocshArg *const caPutJsonLogShowArgs[] = {
        &caPutJsonLogShowArg0
    };
    static const iocshFuncDef caPutJsonLogShowDef = {"caPutJsonLogShow", 1, caPutJsonLogShowArgs};
    static void caPutJsonLogShowCall(const iocshArgBuf *args)
    {
        caPutJsonLogShow(args[0].ival);
    }

    /* Metadata */
    int caPutJsonLogAddMetadata(char *property, char *value){
        CaPutJsonLogTask *logger = CaPutJsonLogTask::getInstance();
        std::string property_str(property);
        std::string value_str(value);
        if (logger != NULL) return logger->addMetadata(property_str, value_str);
        else return -1;
    }
    static const iocshArg caPutJsonLogAddMetadataArg0 = {"property", iocshArgString};
    static const iocshArg caPutJsonLogAddMetadataArg1 = {"value", iocshArgString};
    static const iocshArg *const caPutJsonLogAddMetadataArgs[] =
    {
        &caPutJsonLogAddMetadataArg0,
        &caPutJsonLogAddMetadataArg1
    };
    static const iocshFuncDef caPutJsonLogAddMetadataDef = {"caPutJsonLogAddMetadata", 2, caPutJsonLogAddMetadataArgs};
    static void caPutJsonLogAddMetadataCall(const iocshArgBuf *args)
    {
        caPutJsonLogAddMetadata(args[0].sval, args[1].sval);
    }

    /* Register IOCsh commands */
    static void caPutJsonLogRegister(void)
    {
        static int done = FALSE;
        if(done) return;
        done = TRUE;

        iocshRegister(&caPutjsonLogInitDef,caPutJsonLogInitCall);
        iocshRegister(&caPutJsonLogReconfDef,caPutJsonLogReconfCall);
        iocshRegister(&caPutJsonLogShowDef,caPutJsonLogShowCall);
        iocshRegister(&caPutJsonLogAddMetadataDef,caPutJsonLogAddMetadataCall);
    }
    epicsExportRegistrar(caPutJsonLogRegister);

    epicsExportAddress(int,caPutLogJsonMsgQueueSize);
}
