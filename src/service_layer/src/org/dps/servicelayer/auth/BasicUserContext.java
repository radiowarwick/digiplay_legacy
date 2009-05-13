package org.dps.servicelayer.auth;

public class BasicUserContext implements IUserContext {

	@Override
	public Long currentUserID() {
		return Long.valueOf(1);
	}

}
