package org.dps.servicelayer.auth;

import org.dps.servicelayer.common.PermissionedItem;
import org.dps.servicelayer.dto.File;

public interface IFileAuthoriser {
	<T extends File, U extends PermissionedItem<T>> U getFileAuthorisation(T item, U holder);
	
//	<T extends File, U extends PermissionedItem<V>, V extends SummaryItem<T>> U getFileSummaryAuthorisation(
//			T item_, U holder_, V summary_);
}
