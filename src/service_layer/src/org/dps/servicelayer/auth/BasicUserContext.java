package org.dps.servicelayer.auth;

public class BasicUserContext implements IUserContext {

	public Long currentUserID() {
		return Long.valueOf(1);
	}

}
