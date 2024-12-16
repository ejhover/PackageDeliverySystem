/**
Copyright (c) 2019 Dan Orban
*/

#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <map>
#include <string>
#include <vector>

#include "libwebsockets.h"
#include "libwebsockets/lws-service.h"

/**
 * @class WebServerBase
 * @brief A collection of WebServer and JSON methods for the Simulation.
 **/
class WebServerBase {
 public:
  WebServerBase(int port = 8081, const std::string& webDir = ".");
  virtual ~WebServerBase();

  /**
   * @class Session
   * @brief Base class to represent a session in Json which can send and receive messages and update.
   **/
  class Session {
    friend class WebServerBase;

   public:
    Session();
    virtual ~Session();
    virtual int getId() const { return id; }
    virtual void receiveMessage(const std::string& msg) {}
    virtual void sendMessage(const std::string& msg);
    virtual void update() {}
    virtual void onWrite();

   private:
    void* state;
    int id;
  };

  void service(int time = 10);

  virtual void createSession(void* info);

 protected:
  virtual Session* createSession() { return new Session(); }

 public:
  lws_context* context = nullptr;
  std::vector<Session*> sessions;
  std::map<int, Session*> sessionMap;
  std::string webDir;
};

/**
 * @class WebServer
 * @brief Web server without a STATE which allows for the creation of web server
 *sessions of type T.
 **/
template <typename T>
class WebServer : public WebServerBase {
 public:
  WebServer(int port = 8081, const std::string& webDir = ".")
      : WebServerBase(port, webDir) {}

 protected:
  Session* createSession() { return new T(); }
};

/**
 * @class WebServerWithState
 * @brief Web server with a STATE which allows for the creation of web server
 *sessions of type T and their respective STATE.
 **/
template <typename T, typename STATE>
class WebServerWithState : public WebServerBase {
 public:
  WebServerWithState(STATE state, int port = 8081,
                     const std::string& webDir = ".")
      : WebServerBase(port, webDir), state(state) {}

 protected:
  Session* createSession() { return new T(state); }

 private:
  STATE state;
};

// JSON support
#include "picojson.h"

/**
 * @class JSONSession
 * @brief Provides JSON functions to handle sessions and messages in the
 *simulation.
 **/
class JSONSession : public WebServerBase::Session {
 public:
  virtual void receiveJSON(picojson::value& val) {}

  virtual void sendJSON(picojson::value& val) { sendMessage(val.serialize()); }

  void receiveMessage(const std::string& msg) {
    static std::string buf = "";
    picojson::value val;
    std::string err = picojson::parse(val, msg);
    if (err.empty() && val.is<picojson::object>()) {
      buf = "";
      receiveJSON(val);
    } else {
      buf += msg;
      err = picojson::parse(val, buf);
      if (err.empty() && val.is<picojson::object>()) {
        buf = "";
        receiveJSON(val);
      }
    }
  }
};

#include "util/json.h"

/**
 * @class JsonSession
 * @brief A kind of JSONSession which handle commands in JSON format and process
 *commands in Json.
 **/
class JsonSession : public JSONSession {
 public:
  /**
   * @brief Receive a command from the web server
   * @param val: the command (in JSON format)
   */
  void receiveJSON(picojson::value& val) {
    JsonObject data = JsonValue(val);

    std::string cmd = data["command"];

    JsonObject returnValue;
    returnValue["id"] = data["id"];

    receiveCommand(cmd, data, returnValue);
    JsonValue retVal(returnValue);
    sendJSON(retVal.getValue());
  }

  /**
   * @brief Handles specific commands from the web server
   * @param cmd: command
   * @param data: data (JSON)
   * @param returnValue: return value (JSON) which will be sent back to the
   * server
   */
  virtual void receiveCommand(const std::string& cmd, const JsonObject& data,
                              JsonObject& returnValue) = 0;
};

#endif  // WEBSERVER_H_
