package com.socialnetwork.app.domain;

public class MessageDTO {

    private final String fromMessage;
    private final String toMessage;

    public MessageDTO(String fromMessage, String toMessage) {
        this.fromMessage = fromMessage;
        this.toMessage = toMessage;
    }


}