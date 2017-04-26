#ifndef GENERICVARIABLES_REQUEST_HPP
#define GENERICVARIABLES_REQUEST_HPP

#include "security.hpp"
class QString;
//Request Variables
const QString RequestURL = "https://api.twitch.tv/kraken";
const QString FollowRequestURL = RequestURL + "/streams/followed";
const QString OAuthGenenerationRequestURL = RequestURL + "/oauth2/authorize?response_type=token&client_id=" + ClientID + "&redirect_uri=http://localhost&scope=user_read";
const QString LivestreamerDownloadURL = "http://docs.livestreamer.io/install.html";
const QString GenericIconRequestURL = "http://static-cdn.jtvnw.net/ttv-static/404_preview.jpg";
const QString TwitchApiVersion = "application/vnd.twitchtv.v5+json";

#endif

