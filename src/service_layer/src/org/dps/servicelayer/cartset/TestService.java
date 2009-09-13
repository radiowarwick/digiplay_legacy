package org.dps.servicelayer.cartset;

import org.dps.servicelayer.common.PermissionFault;
import org.dps.servicelayer.dto.Cartset;

public class TestService implements ICartsetService {

	public Long addCartset(Cartset cartset_) throws PermissionFault {
		System.out.print(cartset_.getName());
		return Long.valueOf(-1);
	}

	public void deleteCartset(CartsetRequest request_) throws CartsetNotFoundFault,
			PermissionFault {
		System.out.print(request_.getCartsetID());

	}

	public Cartset getCartset(CartsetRequest request_)
			throws CartsetNotFoundFault, PermissionFault {
		System.out.print(request_.getCartsetID());
		return null;
	}

	public Cartsets getCartsets(CartsetsRequest request_) {
		System.out.print(request_.getResultsPerPage());
		return null;
	}

	public void updateCartset(Cartset cartset_) throws CartsetNotFoundFault,
			PermissionFault {
		System.out.print(cartset_.getName());
	}

}
