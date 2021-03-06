//
// Generated file, do not edit! Created by opp_msgc 4.1 from PON/common_pon/EPON_messages.msg.
//

#ifndef _EPON_MESSAGES_M_H_
#define _EPON_MESSAGES_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "Ethernet.h"
#include "EtherFrame_m.h"
#include "MACAddress.h"
#include <inttypes.h>
// }}



/**
 * Class generated from <tt>PON/common_pon/EPON_messages.msg</tt> by opp_msgc.
 * <pre>
 * packet SyncCode
 * {
 *     char code;
 * }
 * </pre>
 */
class SyncCode : public ::cPacket
{
  protected:
    char code_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SyncCode&);

  public:
    SyncCode(const char *name=NULL, int kind=0);
    SyncCode(const SyncCode& other);
    virtual ~SyncCode();
    SyncCode& operator=(const SyncCode& other);
    virtual SyncCode *dup() const {return new SyncCode(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual char getCode() const;
    virtual void setCode(char code_var);
};

inline void doPacking(cCommBuffer *b, SyncCode& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SyncCode& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>PON/common_pon/EPON_messages.msg</tt> by opp_msgc.
 * <pre>
 * packet EtherFrameWithLLID {
 *     uint16_t llid;
 *     uint8_t channel;
 * }
 * </pre>
 */
class EtherFrameWithLLID : public ::cPacket
{
  protected:
    uint16_t llid_var;
    uint8_t channel_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const EtherFrameWithLLID&);

  public:
    EtherFrameWithLLID(const char *name=NULL, int kind=0);
    EtherFrameWithLLID(const EtherFrameWithLLID& other);
    virtual ~EtherFrameWithLLID();
    EtherFrameWithLLID& operator=(const EtherFrameWithLLID& other);
    virtual EtherFrameWithLLID *dup() const {return new EtherFrameWithLLID(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual uint16_t getLlid() const;
    virtual void setLlid(uint16_t llid_var);
    virtual uint8_t getChannel() const;
    virtual void setChannel(uint8_t channel_var);
};

inline void doPacking(cCommBuffer *b, EtherFrameWithLLID& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, EtherFrameWithLLID& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>PON/common_pon/EPON_messages.msg</tt> by opp_msgc.
 * <pre>
 * packet MPCP extends EthernetIIFrame
 * {
 *     uint16_t opcode;
 *     uint32_t ts;
 * }
 * </pre>
 */
class MPCP : public ::EthernetIIFrame
{
  protected:
    uint16_t opcode_var;
    uint32_t ts_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MPCP&);

  public:
    MPCP();
    MPCP(const MPCP& other);
    virtual ~MPCP();
    MPCP& operator=(const MPCP& other);
    virtual MPCP *dup() const {return new MPCP(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual uint16_t getOpcode() const;
    virtual void setOpcode(uint16_t opcode_var);
    virtual uint32_t getTs() const;
    virtual void setTs(uint32_t ts_var);
};

inline void doPacking(cCommBuffer *b, MPCP& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MPCP& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>PON/common_pon/EPON_messages.msg</tt> by opp_msgc.
 * <pre>
 * packet MPCPGate extends MPCP
 * {
 *     int64 startTimeReport;
 *     uint8_t durationReport;
 *     uint8_t nbSlots;
 *     int64 startTimeBurst[];
 *     uint16_t durationBurst[];
 *     uint8_t channelBurst[];
 * }
 * </pre>
 */
class MPCPGate : public ::MPCP
{
  protected:
    int64 startTimeReport_var;
    uint8_t durationReport_var;
    uint8_t nbSlots_var;
    int64 *startTimeBurst_var; // array ptr
    unsigned int startTimeBurst_arraysize;
    uint16_t *durationBurst_var; // array ptr
    unsigned int durationBurst_arraysize;
    uint8_t *channelBurst_var; // array ptr
    unsigned int channelBurst_arraysize;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MPCPGate&);

  public:
    MPCPGate();
    MPCPGate(const MPCPGate& other);
    virtual ~MPCPGate();
    MPCPGate& operator=(const MPCPGate& other);
    virtual MPCPGate *dup() const {return new MPCPGate(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int64 getStartTimeReport() const;
    virtual void setStartTimeReport(int64 startTimeReport_var);
    virtual uint8_t getDurationReport() const;
    virtual void setDurationReport(uint8_t durationReport_var);
    virtual uint8_t getNbSlots() const;
    virtual void setNbSlots(uint8_t nbSlots_var);
    virtual void setStartTimeBurstArraySize(unsigned int size);
    virtual unsigned int getStartTimeBurstArraySize() const;
    virtual int64 getStartTimeBurst(unsigned int k) const;
    virtual void setStartTimeBurst(unsigned int k, int64 startTimeBurst_var);
    virtual void setDurationBurstArraySize(unsigned int size);
    virtual unsigned int getDurationBurstArraySize() const;
    virtual uint16_t getDurationBurst(unsigned int k) const;
    virtual void setDurationBurst(unsigned int k, uint16_t durationBurst_var);
    virtual void setChannelBurstArraySize(unsigned int size);
    virtual unsigned int getChannelBurstArraySize() const;
    virtual uint8_t getChannelBurst(unsigned int k) const;
    virtual void setChannelBurst(unsigned int k, uint8_t channelBurst_var);
};

inline void doPacking(cCommBuffer *b, MPCPGate& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MPCPGate& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>PON/common_pon/EPON_messages.msg</tt> by opp_msgc.
 * <pre>
 * packet MPCPReport extends MPCP
 * {
 *     uint32_t lengthSlot;
 * }
 * </pre>
 */
class MPCPReport : public ::MPCP
{
  protected:
    uint32_t lengthSlot_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MPCPReport&);

  public:
    MPCPReport();
    MPCPReport(const MPCPReport& other);
    virtual ~MPCPReport();
    MPCPReport& operator=(const MPCPReport& other);
    virtual MPCPReport *dup() const {return new MPCPReport(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual uint32_t getLengthSlot() const;
    virtual void setLengthSlot(uint32_t lengthSlot_var);
};

inline void doPacking(cCommBuffer *b, MPCPReport& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MPCPReport& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>PON/common_pon/EPON_messages.msg</tt> by opp_msgc.
 * <pre>
 * packet MPCPRegReq extends MPCP
 * {
 *     uint8_t ptpNumReq;
 *     bool wdmEnabled;
 * }
 * </pre>
 */
class MPCPRegReq : public ::MPCP
{
  protected:
    uint8_t ptpNumReq_var;
    bool wdmEnabled_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MPCPRegReq&);

  public:
    MPCPRegReq();
    MPCPRegReq(const MPCPRegReq& other);
    virtual ~MPCPRegReq();
    MPCPRegReq& operator=(const MPCPRegReq& other);
    virtual MPCPRegReq *dup() const {return new MPCPRegReq(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual uint8_t getPtpNumReq() const;
    virtual void setPtpNumReq(uint8_t ptpNumReq_var);
    virtual bool getWdmEnabled() const;
    virtual void setWdmEnabled(bool wdmEnabled_var);
};

inline void doPacking(cCommBuffer *b, MPCPRegReq& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MPCPRegReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>PON/common_pon/EPON_messages.msg</tt> by opp_msgc.
 * <pre>
 * packet MPCPRegister extends MPCP
 * {
 *     uint8_t ptpNumReg;
 *     uint16_t LLIDs[];
 * }
 * </pre>
 */
class MPCPRegister : public ::MPCP
{
  protected:
    uint8_t ptpNumReg_var;
    uint16_t *LLIDs_var; // array ptr
    unsigned int LLIDs_arraysize;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MPCPRegister&);

  public:
    MPCPRegister();
    MPCPRegister(const MPCPRegister& other);
    virtual ~MPCPRegister();
    MPCPRegister& operator=(const MPCPRegister& other);
    virtual MPCPRegister *dup() const {return new MPCPRegister(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual uint8_t getPtpNumReg() const;
    virtual void setPtpNumReg(uint8_t ptpNumReg_var);
    virtual void setLLIDsArraySize(unsigned int size);
    virtual unsigned int getLLIDsArraySize() const;
    virtual uint16_t getLLIDs(unsigned int k) const;
    virtual void setLLIDs(unsigned int k, uint16_t LLIDs_var);
};

inline void doPacking(cCommBuffer *b, MPCPRegister& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MPCPRegister& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>PON/common_pon/EPON_messages.msg</tt> by opp_msgc.
 * <pre>
 * packet MPCPRegAck extends MPCP
 * {
 * }
 * </pre>
 */
class MPCPRegAck : public ::MPCP
{
  protected:

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MPCPRegAck&);

  public:
    MPCPRegAck();
    MPCPRegAck(const MPCPRegAck& other);
    virtual ~MPCPRegAck();
    MPCPRegAck& operator=(const MPCPRegAck& other);
    virtual MPCPRegAck *dup() const {return new MPCPRegAck(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
};

inline void doPacking(cCommBuffer *b, MPCPRegAck& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MPCPRegAck& obj) {obj.parsimUnpack(b);}


#endif // _EPON_MESSAGES_M_H_
